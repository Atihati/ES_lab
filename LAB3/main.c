#include <msp430.h> 
#include <halGeneral.h>
#include <stdint.h>
#include <halGpio.h>
#include "halUCS.h"
#include "halTimerB0.h"

#define RUN_TESTS                   // auskommentieren für den Normalbetrieb

#ifdef RUN_TESTS
#include "testHalGeneral.h"
#endif


extern volatile ButtonCom CCButton;

/**
 * main.c
 */


void main(void)
{
    halInit();

#ifdef RUN_TESTS
    halInitTest();
#endif

    while(1)
        {
            //LCD_BL_TOGGLE;          // Hintergrundbeleuchtung umschalten
            //delayMsBlocked(250);    // 250 ms blockierend warten
        }
}
