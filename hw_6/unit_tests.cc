#include "gtest/gtest.h"
#include "elma/elma.h"
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "integrator.h"
#include <iostream>
#include <chrono>


#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

using namespace std;
using namespace elma;



namespace {
    class Constant : public Process {
        public:
            Constant(std::string name) : Process(name) {}
            void init(){}
            void start() {}
            void update() {
                channel("link").send(5);
            }
            void stop() {}
    };

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

    TEST(Channel, Random){
        elma::Manager m;

        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);
    }

    TEST(Channel, Integral){
        elma::Manager m;

        Integrator r("Int");
        Constant c("Constant");
        elma::Channel link("link");

        m.schedule(c, 1_ms)
        .schedule(r, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);
    }
}