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

    if (steerVal < -100) steerVal = -100;
    else if (steerVal > 100) steerVal = 100;

    TA1CCR2 = (ST_MIDDLE - 50 + 10 * steerVal);
    /*if (steerVal < 0)
    //{
        /// Negative side [-100, 0) -> [ST_maxLeft, ST_MIDDLE]
        tickVal = (int)ST_MIDDLE + (((int)steerVal * ((int)ST_MIDDLE - (int)ST_maxLeft)) / 100);
    }
    else
    {
        // Positive side [0, 100] -> [ST_MIDDLE, ST_maxRight]
        tickVal = (int)ST_MIDDLE + (((int)steerVal * ((int)ST_maxRight - (int)ST_MIDDLE)) / 100);
    }

    setSteerServo = tickVal;
    halTimerA1SetSteering(tickVal);*/
}

void driverSetThrottle(signed char throttleVal)
{
    /*unsigned int tickVal;

    // Wertebereich begrenzen (-100 bis +100)
    if (throttleVal < -100)
    {
        throttleVal = -100;
    }
    else if (throttleVal > 100)
    {
        throttleVal = 100;
    }

    // Skalierung für Fahrregler (Throttle) mit explizitem signed-Casting
    if (throttleVal < 0)
    {
        // Rückwärtsbereich: Mapping von [-100, 0) auf [MaxRPW, MinRPW]
        tickVal = (int)MinRPW + (((int)throttleVal * ((int)MinRPW - (int)MaxRPW)) / 100);
    }
    else
    {
        // Vorwärtsbereich: Mapping von [0, +100] auf [MinFPW, MaxFPW]
        tickVal = (int)MinFPW + (((int)throttleVal * ((int)MaxFPW - (int)MinFPW)) / 100);
    }

    setThrottle = tickVal;
    halTimerA1SetThrottle(tickVal);*/
    if (throttleVal > 100) throttleVal = 100;
        if (throttleVal < -100) throttleVal = -100;

        if (throttleVal > 0)
        {
            TA1CCR1 = MinFPW + 25 * throttleVal;
        }
        else if (throttleVal < 0)
        {
            TA1CCR1 = MinFPW + 25 * throttleVal;
        }
        else // value == 0
        {
            TA1CCR1 = MaxBreak;
        }
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
