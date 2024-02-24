#include "random_process.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "elma/elma.h"


using namespace elma;
using namespace std;

void RandomProcess::init(){
    srand((unsigned)time(NULL));
}

void RandomProcess::update(){
    double num = static_cast<double>(rand()) / (RAND_MAX - 1);
    channel("link").send(num);
    //cout<<num<<endl;
}