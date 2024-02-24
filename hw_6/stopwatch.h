#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <chrono>

using namespace std::chrono;

class Stopwatch {

    public:
        Stopwatch(){}
        void start();              // starts the timer
        void stop();               // stops the timer
        void reset();              // sets stopwatch to zero
        double get_minutes();      // number of minutes counted, as a double
        double get_seconds();      // number of seconds counted, as a double
        double get_milliseconds(); // number of milliseconds counted, as a double
        double get_nanoseconds();  // number of nanoseconds counted, as a double
    
    private:
        high_resolution_clock::time_point start_time;
        high_resolution_clock::time_point end_time;
        high_resolution_clock::duration elapsed_time;
        bool started = false;
};

#endif