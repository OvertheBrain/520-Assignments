#include "elma/elma.h"
#include <vector>
#include <iostream>
#include "filter.h"


using namespace elma;
using namespace std;

void Filter::init(){
    avg = 0;
    received = {};
}

void Filter::update(){
    if ( channel("link").nonempty() ) {
        received.push_back(channel("link").latest());
    }


    if(received.size() <= 10){
        double sum = accumulate(received.begin(), received.end(), 0.0);
        avg = sum / received.size();
    }
    else{
        auto i = received.end() - 10;
        double sum = accumulate(i, received.end(), 0.0);
        avg = (double) sum / 10;
    }

    cout<<value()<<endl;
}