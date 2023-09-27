#include <Arduino.h>

#include "Timer.h"

Timer::Timer(float hz)
{
    this->timeout = 1000.0f / hz;
}

bool Timer::shouldRun()
{
    const unsigned long actualTime = millis();
    const bool shouldRun = actualTime - last > timeout;

    if (shouldRun)
    {
        last = actualTime;
    }

    return shouldRun;
}