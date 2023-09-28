#pragma once

#include "config.h"

struct Context
{
    int T1 = 1;
    int T2 = 1;
    int T3 = 1;
    bool K1 = false;
    bool K2 = false;
    bool K3 = false;
    Config *config;
};

Context *createContext();