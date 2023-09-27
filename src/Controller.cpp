#include <Arduino.h>
#include "Controller.h"
#include "pinout.h"

void Controller::begin(Config *config)
{
    this->config = config;

    pinMode(TH_1, INPUT);
    pinMode(TH_2, INPUT);
    pinMode(TH_3, INPUT);

    pinMode(SW_1, OUTPUT);
    pinMode(SW_2, OUTPUT);
    pinMode(SW_3, OUTPUT);
}

void Controller::loop()
{
    if (!this->timer.shouldRun())
    {
        return;
    }

    bool th_1 = false;
    bool th_2 = false;
    bool th_3 = false;

    for (int i = 0; i < SAMPLE_HZ; i++)
    {
        th_1 = th_1 || !digitalRead(TH_1);
        th_2 = th_2 || !digitalRead(TH_2);
        th_3 = th_3 || !digitalRead(TH_3);
        delay(1000 / SAMPLE_HZ);
    }

    context.T1 = th_1 + 1;
    context.T2 = th_2 + 1;
    context.T3 = th_3 + 1;

    unsigned int *profile = this->config->profile.getActiveProfile();

    context.K1 = ((profile[0] & 3 & context.T1) && ((profile[0] >> 2) & 3 & context.T2) && ((profile[0] >> 4) & 3 & context.T3));
    context.K2 = ((profile[1] & 3 & context.T1) && ((profile[1] >> 2) & 3 & context.T2) && ((profile[1] >> 4) & 3 & context.T3));
    context.K3 = ((profile[2] & 3 & context.T1) && ((profile[2] >> 2) & 3 & context.T2) && ((profile[2] >> 4) & 3 & context.T3));

    digitalWrite(SW_1, context.K1);
    digitalWrite(SW_2, context.K2);
    digitalWrite(SW_3, context.K3);
}

Context *Controller::getContext()
{
    return &(this->context);
}