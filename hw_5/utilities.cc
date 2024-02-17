#include "utilities.h"
#include "typed_array.h"
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;


void sort_by_magnitude(vector<double> &v){
    sort(v.begin(), v.end(), [](double a, double b){return abs(a) < abs(b);});
}


TypedArray<TypedArray<double>> read_matrix_csv(const string path){
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    TypedArray<TypedArray<double>> res;
    string line;
    int column = -1;

    try{
        while (getline(file, line)) {
            stringstream ss(line);
            TypedArray<double> row;
            string cell;
            int rowLength = 0;

            // Read the row
            while (getline(ss, cell, ',')) {
                // Trim spaces and tabs
                cell.erase(remove_if(cell.begin(), cell.end(), [](char c) { return isspace(c); }), cell.end());
                if (!cell.empty()) {
                    row.set(rowLength++, stod(cell));
                }
            }

            // Check if it can be a matrix
            if (column == -1) {
                column = rowLength;
            } else if (rowLength != column) {
                throw runtime_error("Irregular matrix dimensions");
            }

            res.push(row);
        }

    } catch(exception e) {
        throw runtime_error("The CSV does not represent a matrix");
    }

    return res;
}

void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path){
    ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.safe_get(i).size(); j++) {
            file << matrix.safe_get(i).get(j);
            if (j < matrix.safe_get(i).size() - 1) file << ", ";
        }
        file << "\n";
    }
}

map<string, int> occurrence_map(const string path){
    map<string, int> res;

    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string word;
        while (stream >> word) {
            // Remove invalid characters
            word.erase(remove_if(word.begin(), word.end(), [](char c) {
                    return !isalnum(c) && c != '\'';
                }), 
                word.end());

            // Convert to lowercase
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (!word.empty()) {
                res[word]++;
            }
        }
    }

    return res;
}