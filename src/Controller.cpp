#include <Arduino.h>
#include "Controller.h"
#include "pinout.h"

void Controller::begin(Context *context)
{
    this->context = context;

    pinMode(T_1, INPUT);
    pinMode(T_2, INPUT);
    pinMode(T_3, INPUT);

    pinMode(K_1, OUTPUT);
    pinMode(K_2, OUTPUT);
    pinMode(K_3, OUTPUT);
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
        th_1 = th_1 || !digitalRead(T_1);
        th_2 = th_2 || !digitalRead(T_2);
        th_3 = th_3 || !digitalRead(T_3);
        delay(1000 / SAMPLE_HZ);
    }

    context->T1 = th_1 + 1;
    context->T2 = th_2 + 1;
    context->T3 = th_3 + 1;

    unsigned int *profile = context->config->profile.getActiveProfile();

    context->K1 = ((profile[0] & 3 & context->T1) && ((profile[0] >> 2) & 3 & context->T2) && ((profile[0] >> 4) & 3 & context->T3));
    context->K2 = ((profile[1] & 3 & context->T1) && ((profile[1] >> 2) & 3 & context->T2) && ((profile[1] >> 4) & 3 & context->T3));
    context->K3 = ((profile[2] & 3 & context->T1) && ((profile[2] >> 2) & 3 & context->T2) && ((profile[2] >> 4) & 3 & context->T3));

    digitalWrite(K_1, context->K1);
    digitalWrite(K_2, context->K2);
    digitalWrite(K_3, context->K3);
}