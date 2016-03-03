#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <string>
#include <time.h>

namespace qst {

class StopWatch
{
public:
    StopWatch();

    double secondsElapsed();
    void start();
    void stop();
    std::string str();

private:
    double mSecondsElapsed;
    struct timespec mStart;
};

}

#endif
