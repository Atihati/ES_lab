/*
 * halTimerA1.c
 *
 *  Created on: 24.10.2026
 *      Author: hrabo
 */
#include "halTimerA1.h"
#include "halGpio.h"

// Periodenzähler für die createPulses()-Warteschleife
static volatile unsigned int periodCounter = 0;

void halTimerA1Init(void)
{
    TA1CTL = TACLR;                 // Clear timer and control registers cleanly
    TA1CTL = TASSEL__SMCLK;         // Clock source: Sub-Master CLK

    // CCTL0 => Period Channel (Compare mode)
    TA1CCTL0 &= ~CCIFG;             // Clear interrupt flag
    TA1CCTL0 &= ~COV;               // Clear capture overflow
    TA1CCTL0 &= ~CAP;               // Compare mode (not capture)
    TA1CCTL0 |= CCIE;               // Interrupt aktivieren, damit periodCounter mitzählt!

    // CCTL1 => Throttle (PWM Output)
    TA1CCTL1 &= ~CCIFG;             // Clear interrupt flag
    TA1CCTL1 &= ~COV;               // Clear capture overflow
    TA1CCTL1 &= ~CAP;               // Compare mode
    TA1CCTL1 |= OUTMOD_7;           // Output mode: Reset/Set (PWM)

    // CCTL2 => Steering (PWM Output)
    TA1CCTL2 &= ~CCIFG;             // Clear interrupt flag
    TA1CCTL2 &= ~COV;               // Clear capture overflow
    TA1CCTL2 &= ~CAP;               // Compare mode
    TA1CCTL2 |= OUTMOD_7;           // Output mode: Reset/Set (PWM)

    // Load Period and Duty Cycle values using clean assignments (=)
    TA1CCR0  = PWM_60HZ;            // Period (2.5MHz / 60Hz => ~41667)
    TA1CCR1  = 0x0;                 // Throttle duty cycle => 0%
    TA1CCR2  = 0x0;                 // Steering duty cycle => 0%

    TA1CTL  |= MC__UP;              // Start timer in Up mode
}

void halTimerA1SetSteering(unsigned int width)
{
    TA1CCR2 = width;
}

void halTimerA1SetThrottle(unsigned int width)
{
    TA1CCR1 = width;
}

void halTimerA1ResetPeriodCnt(void)
{
    periodCounter = 0;
}

unsigned int halTimerA1GetPeriodCnt(void)
{
    return periodCounter;
}

// Interrupt-Service-Routine für Timer 1 (CCR0), zählt jede PWM-Periode
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    periodCounter++;
}
