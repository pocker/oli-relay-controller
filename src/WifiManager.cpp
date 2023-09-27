#include "WifiManager.h"

#include <Arduino.h>
#include <WiFi.h>

void WifiManager::begin(Config *config)
{
    this->config = config;
    WiFi.begin();
}

void WifiManager::loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        this->initialConnection = true;
        return;
    }

    if (this->apMode)
    {
        return;
    }

    if (this->shouldHostAP())
    {
        this->hostAP();
    }
    else if (millis() - this->lastTry > this->CONNECTION_TIMEOUT)
    {
        this->connect();
    }
}

bool WifiManager::shouldHostAP()
{
    return strlen(config->wifi.ssid) == 0 || strlen(config->wifi.password) == 0 || (millis() > this->AP_MODE_TIMEOUT && !this->initialConnection);
}

void WifiManager::connect()
{
    struct Wifi &wifi = config->wifi;
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi.ssid, wifi.password);
    this->lastTry = millis();
}

void WifiManager::hostAP()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(this->DEFAULT_SSID, this->DEFAULT_PASSWORD);
    this->apMode = true;
}