#pragma once

#include "config.h"

class WifiManager
{

private:
    static const int CONNECTION_TIMEOUT = 1000 * 10; // 10 sec
    static const int AP_MODE_TIMEOUT = 1000 * 60;  // 1 min
    static constexpr const char *DEFAULT_SSID = "relay-controller";
    static constexpr const char *DEFAULT_PASSWORD = "12345678";

    Config *config;

    bool initialConnection;
    unsigned long lastTry = (unsigned long)-1;
    bool apMode = false;

    void connect();
    void hostAP();
    bool shouldHostAP();

public:
    void begin(Config *);
    void loop();
};