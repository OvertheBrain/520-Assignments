#include "gtest/gtest.h"
#include "elma/elma.h"
#include "stopwatch.h"
#include <iostream>
#include <chrono>


#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

using namespace std;

namespace {
    TEST(Watch, Test){
        Stopwatch w; // should set the stopwatch to 0 seconds
        w.start();
        SLEEP;
        w.stop();
        cout << w.get_seconds() << "\n"; // about 1.5
        SLEEP;
        cout << w.get_seconds() << "\n"; // still about 1.5
        w.start();
        SLEEP;
        w.stop();
        cout << w.get_seconds() << "\n"; // about 3.0
        w.reset();
        cout << w.get_seconds() << "\n"; // 0.0
    }
}