/*
 * driversSensors.c
 *  Created on: 24.10.2026
 *  Author: hrabo
 */

#include "driversSensors.h"
#include "../HAL/halTimerA0.h"

static unsigned long totalDistance = 0;

void driverSensorsInit(void)
{
    halTimerA0Init();
}

unsigned int getSpeed(void)
{
    unsigned int pulses = halTimerA0GetPulseCnt();

    unsigned int speed = (pulses * MM_PER_PULSE * 10);

    return speed;
}

unsigned int getDistance(void)
{
    static unsigned int lastPulses = 0;
    unsigned int currentPulses = halTimerA0GetPulseCnt();

    if (currentPulses != lastPulses)
    {
        totalDistance += (unsigned long)(currentPulses * MM_PER_PULSE);
        lastPulses = currentPulses;
    }

    return (unsigned int)totalDistance;
}
