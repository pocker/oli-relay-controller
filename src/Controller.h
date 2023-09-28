#pragma once
#include "context.h"
#include "Timer.h"

#define SAMPLE_HZ 60

class Controller
{
private:
    Timer timer;
    Context* context;

public:
    Controller() : timer(2.0f) {}
    void begin(Context *);
    void loop();
};
