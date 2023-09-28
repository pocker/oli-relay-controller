#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "Controller.h"
#include "config.h"

class Monitor
{
private:
    Context *context;

public:
    void begin(Context *);
    void write(AsyncResponseStream *);
};