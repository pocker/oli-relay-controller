#pragma once

class Timer
{
private:
    unsigned int timeout;
    unsigned long last;

public:
    Timer(float);
    bool shouldRun();
};