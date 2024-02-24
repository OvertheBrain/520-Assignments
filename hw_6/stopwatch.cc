#include <iostream>
#include <ratio>
#include <chrono>
#include "stopwatch.h"


using namespace std::chrono;

void Stopwatch::start(){
    if (!started) {
        start_time = high_resolution_clock::now();
        started = true;
    }
}

void Stopwatch::stop(){
    if(started){
        end_time = high_resolution_clock::now();
        started = false;
        elapsed_time += end_time - start_time;
    }
}

void Stopwatch::reset(){
    started = false;
    elapsed_time = high_resolution_clock::now() - high_resolution_clock::now();
}

double Stopwatch::get_seconds(){
    return duration<double, std::ratio<1, 1>>(elapsed_time).count();
}

double Stopwatch::get_milliseconds(){
    return duration<double, std::milli>(elapsed_time).count();
}

double Stopwatch::get_minutes(){
    return duration<double, std::ratio<60, 1>>(elapsed_time).count();
}

double Stopwatch::get_nanoseconds(){
    return duration<double, std::nano>(elapsed_time).count();
}