/*
 * driversSensors.c
 */

#include "driversSensors.h"
#include "../HAL/halTimerA0.h"

// Variable zur Aufsummierung des Gesamtwegs
static unsigned long totalDistance = 0;

void driverSensorsInit(void)
{
    halTimerA0Init();
}

unsigned int getSpeed(void)
{
    unsigned int pulses = halTimerA0GetPulseCnt();

    // Beispielhafte Umrechnung in mm/s (abhängig von der Länge Ihres Messfensters)
    unsigned int speed = (pulses * MM_PER_PULSE * 10);

    return speed;
}

unsigned int getDistance(void)
{
    static unsigned int lastPulses = 0;
    unsigned int currentPulses = halTimerA0GetPulseCnt();

    // Nur dann zum Gesamtweg addieren, wenn sich der Messwert aktualisiert hat
    // (oder über ein Flag / direkten Aufruf im Messfenster-Ende)
    if (currentPulses != lastPulses)
    {
        totalDistance += (unsigned long)(currentPulses * MM_PER_PULSE);
        lastPulses = currentPulses;
    }

    return (unsigned int)totalDistance;
}
