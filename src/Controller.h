#pragma once
#include "config.h"
#include "Timer.h"

#define SAMPLE_HZ 60

struct Context
{
   int T1 = 1;
   int T2 = 1;
   int T3 = 1;
   bool K1 = false;
   bool K2 = false;
   bool K3 = false;
};


class Controller
{
private:
    Config *config;
    Timer timer;
    Context context;

public:
    Controller() : timer(2.0f) {}
    void begin(Config *);
    void loop();
    Context *getContext();
};
