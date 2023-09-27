#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "Controller.h"
#include "config.h"

class Monitor
{
private:
    Config *config;
    Context *context;

public:
    void begin(Config *, Context *);
    void write(AsyncResponseStream *);
};