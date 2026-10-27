/*
 * halTimerA0.c
 *
 *  Created on: 26.10.2026
 *      Author: hrabo
 */
#include "halTimerA0.h"
#include <msp430.h>

static volatile unsigned int pulseCount = 0;
static volatile unsigned int capturedPulses = 0;

void halTimerA0Init(void)
{
    TA0CTL = TACLR;               // Timer clear
    TA0CTL = TASSEL__SMCLK | MC__UP; // SMCLK, Up-Mode

    // TA0CCR0 als Messfenster (Periodenlänge für das Zeitfenster definieren)
    // Beispielwert (muss an Ihre Vorgaben angepasst werden):
    TA0CCR0 = 50000;
    TA0CCTL0 |= CCIE;             // Interrupt für das Messfenster aktivieren

    // TA0CCR2 im Capture Mode auf beide Flanken konfigurieren (für Drehzahl/Impulse)
    TA0CCTL2 = CM_3 | CCIS_0 | CAP | CCIE; // CM_3 = beide Flanken, CAP = Capture, CCIE = Interrupt
}

unsigned int halTimerA0GetPulseCnt(void)
{
    return capturedPulses;
}

void halTimerA0ResetPulseCnt(void)
{
    pulseCount = 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
    switch (__even_in_range(TA0IV, TA0IV_TA0CCR2))
    {
        case TA0IV_NONE:   break;
        case TA0IV_TA0CCR1: break;
        case TA0IV_TA0CCR2: // Angenommen Sensor liegt auf TA0CCR2
            pulseCount++;   // Flanke mitzählen!
            break;
        case TA0IV_TA0IFG:  break;
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    // Wenn das Messfenster abläuft, sichern wir die Pulse für den Treiber
    capturedPulses = pulseCount;
    pulseCount = 0; // Zähler für das nächste Fenster zurücksetzen
}
