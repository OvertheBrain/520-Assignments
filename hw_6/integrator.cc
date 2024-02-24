#include "elma/elma.h"
#include <iostream>
#include "integrator.h"

using namespace elma;

void Integrator::init(){
    integral = 0.0;
}


void Integrator::update(){
    double v = 0;  
    if ( channel("link").nonempty() ) {
        v = channel("link").latest();
    }

    integral += delta() * v;

    std::cout<<value()<<std::endl;
}