#include <iostream>
#include <vector>     
#include <map>      

using namespace std;

int main() {
    vector<string> vec = {"i", "am", "on", "a", "very", "bumpy", "flight"};
    // Iterate over each element in the vector using a range-based for loop
    for(const auto& str : vec) {
        cout << str << "!"; // Output each string followed by an exclamation mark
        if(&str != &vec.back()) cout << " ";
    }
    cout << endl;

    // Array of integers
    int a[] = {1, 4, 9, 16};
    for(const int& num : a) {
        cout << num;
        if(num != a[size(a)-1]) cout << ", ";
    }
    cout << endl;

    // Map of string and int pairs
    map<string, int> map = {{"John", 30}, {"Jane", 25}, {"Jim", 35}};
    for(const auto& pair : map) {
        cout << pair.first << ": " << pair.second;
        if(&pair != &(*prev(map.end()))) cout << ", ";
    }
    cout << endl;

    return 0;
}