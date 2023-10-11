#include "time.h"
#include <cmath>
#include <iostream>
void timer::start_delayMS(unsigned int ms, unsigned int deltaTime)
{
    if (this->timeStarted <= 0)
    {
        unsigned int framesInMs= floor((ms / 16.66666));
        this->timeStarted = deltaTime;
        this->timeDest = (timeStarted + framesInMs);

    }
}

bool timer::c_delay()
{
    timeStarted++;
    if (this->timeStarted >= timeDest && debounce == false)
    {
        debounce = true;
        return true;

    }
    return false;
}

void timer::start_recursiveTimerMS(unsigned int ms, unsigned int deltaTime)
{
    if (this->timeStarted <= 0) 
    {
        unsigned int framesInMs = floor((ms / 16.66666));
        this->timeStarted = deltaTime;
        this->timeDest = (timeStarted + framesInMs);

    }
}

bool timer::c_recursiveTimerDelay()
{
    timeStarted++;
    if (this->timeStarted >= timeDest)
    {
        timeDest = timeStarted + timeDest;
        return true;
    }
    std::cout << timeStarted << std::endl;
    return false;
}
