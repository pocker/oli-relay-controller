#include "Monitor.h"

#include <Arduino.h>
#include <ArduinoJson.h>

#include "pinout.h"

void Monitor::begin(Config *config, Context *context)
{
    this->config = config;
    this->context = context;
}

void Monitor::write(AsyncResponseStream *response)
{
    DynamicJsonDocument status(1024);
    status["uptime"] = esp_timer_get_time();

    JsonObject inputs = status.createNestedObject("inputs");
    inputs["T_1"] = context->T1;
    inputs["T_2"] = context->T2;
    inputs["T_3"] = context->T3;

    JsonObject outputs = status.createNestedObject("outputs");
    outputs["K_1"] = context->K1;
    outputs["K_2"] = context->K2;
    outputs["K_3"] = context->K3;

    JsonObject config = status.createNestedObject("config");
    JsonObject wifi = config.createNestedObject("wifi");
    wifi["ssid"] = this->config->wifi.ssid;
    JsonObject user = config.createNestedObject("user");
    user["username"] = this->config->user.username;
    JsonObject profile = config.createNestedObject("profile");
    profile["active"] = this->config->profile.active;
    JsonArray configuration = profile.createNestedArray("configuration");

    for (int i = 0; i < MAX_PROFILE; i++)
    {
        JsonArray actualConfig = configuration.createNestedArray();
        for (int j = 0; j < OUTPUTS; j++)
        {
            actualConfig.add(this->config->profile.configuration[i][j]);
        }
    }

    serializeJson(status, *response);
}