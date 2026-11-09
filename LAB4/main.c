#include <msp430.h> 
#include <halGeneral.h>
#include <stdint.h>
#include <halGpio.h>
#include "halUCS.h"
#include "halTimerB0.h"
#include "driverGeneral.h"
#include "driverAktorik.h"
#include "driversSensors.h"
#include "halTimerA0.h"

#define RUN_TESTS                   // auskommentieren für den Normalbetrieb

#ifdef RUN_TESTS
#include "testHalGeneral.h"
#endif


extern volatile ButtonCom CCButton;
unsigned int dist;
unsigned int speed;
unsigned int cnt;
unsigned int speed;

/**
 * main.c
 */


void main(void)
{
    halInit();
//    driverInit();

#ifdef RUN_TESTS
    halInitTest();
#endif

    while(1)
        {
            if (CCButton.active == 1)
            {
                switch (CCButton.button)
                {
                    case START_BUTTON:
                        LCD_BACKLIGHT_ON;
                        driverSetSteering(100);
                        driverSetThrottle(100);
                        break;
                    case STOP_BUTTON:
                        LCD_BACKLIGHT_OFF;
                        driverSetSteering(-100);
                        driverSetThrottle(50);
                        break;
                }

                CCButton.active = 0;   // Clean Flag
            }

            driverSetSteering(100);
            delayMsBlocked(250);

            speed = getSpeed();
            dist = getDistance();
            cnt = halTimerA0GetPulseCnt();

        }
}
