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

/*void driverSetSteering(signed char steerVal)
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

void driverSetSteering(signed char steerVal)
{
    unsigned int tickVal;

    // Wertebereich begrenzen (-100 bis +100)
    if (steerVal < -100)
    {
        steerVal = -100;
    }
    else if (steerVal > 100)
    {
        steerVal = 100;
    }

    if (steerVal < 0)
    {
        // Linksbereich: 850 Ticks Spanne (3650 - 2800) -> 8.5 Ticks pro Prozent (* 85 / 10)
        tickVal = (int)ST_MIDDLE + (((int)steerVal * 85) / 10);
    }
    else
    {
        // Rechtsbereich: 950 Ticks Spanne (4600 - 3650) -> 9.5 Ticks pro Prozent (* 95 / 10)
        tickVal = (int)ST_MIDDLE + (((int)steerVal * 95) / 10);
    }

    setSteerServo = tickVal;
    halTimerA1SetSteering(tickVal);
}
*/

void driverSetSteering(signed char steerVal)
{

    // Wertebereich begrenzen (-100 bis +100)
    if (steerVal < -100)
    {
        steerVal = -100;
    }
    else if (steerVal > 100)
    {
        steerVal = 100;
    }

    if (steerVal < 0)
    {
        setSteerServo = (int)ST_MIDDLE + ((int)steerVal * (((int)ST_MIDDLE - (int)ST_maxLeft) / 10)) / 10;
    }
    else if (steerVal == 0)
    {
        setSteerServo = (int)ST_MIDDLE;
    }
    else
    {
        setSteerServo = (int)ST_MIDDLE + ((int)steerVal * (((int)ST_maxRight - (int)ST_MIDDLE) / 10)) / 10;
    }
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
