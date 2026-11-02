/*
 * driverAktorik.c
 *
 *  Created on: 24.10.2026
 *      Author: hrabo
 */

#include <msp430.h>
#include "driverAktorik.h"
#include "halTimerA1.h"

unsigned int setSteerServo, setThrottle;
extern volatile int speedControllerImpulse;

void driverSetSteering(signed char steerVal)
{

    if (steerVal < -100)
    {
        steerVal = -100;
    }
    else if (steerVal > 100)
    {
        steerVal = 100;
    }

    setSteerServo = (int)ST_MIDDLE + (((int)steerVal * 125) / 10);

    halTimerA1SetSteering(setSteerServo);
}

void driverSetThrottle(signed char throttleVal)
{

        // Wertebereich begrenzen (-100 bis +100)
        if (throttleVal < -100)
        {
            throttleVal = -100;
        }
        else if (throttleVal > 100)
        {
            throttleVal = 100;
        }

        // Skalierung für Fahrregler (Throttle):
        if (throttleVal < 0)
        {
            setThrottle = (int)MinRPW + 25 * throttleVal;
        }
        else if (throttleVal > 0)
        {
            // Vorwärtsbereich: Startet bei MinFPW und skaliert hoch bis MaxFPW.
            //setThrottle = (int)MinFPW + (((int)throttleVal * ((int)MaxFPW - (int)MinFPW)) / 100);
            setThrottle = (int)MinFPW + 25 * throttleVal;
        }
        else
        {
            setThrottle = (int)MaxBreak;
        }
        halTimerA1SetThrottle(setThrottle);
}

void driverSetBreak(signed char motorBreak)
{
    if (motorBreak)
    {
        halTimerA1SetThrottle(MaxBreak);
    }
    else
    {
        halTimerA1SetThrottle(MinRPW); // Oder Neutralstellung
    }
}

void driverESCinit(void)
{
    createPulses(MaxRPW, 131);
    createPulses(MinRPW, 131);
    createPulses(MinFPW, 131);
    createPulses(MaxFPW, 131);
    createPulses(MaxBreak, 30);
}

void createPulses(int pwm, int pulseDuration)
{
    halTimerA1SetThrottle(pwm);                    // einmal setzen reicht
    halTimerA1ResetPeriodCnt();
    while(halTimerA1GetPeriodCnt() <= pulseDuration);
}
