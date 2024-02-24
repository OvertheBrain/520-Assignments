#ifndef _FILTER_H
#define _FILTER_H

#include "elma/elma.h"
#include <vector>

using namespace elma;
using namespace std;

class Filter : public Process {
    public:
        Filter(std::string name) : Process(name) {}
        void init();
        void start() {}
        void update();
        void stop() {}

        double value() {
            return avg;
        }

    private:
        double avg = 0;
        vector<double> received;
};



#endif