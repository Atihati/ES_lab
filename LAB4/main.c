#include <msp430.h> 
#include <halGeneral.h>
#include <stdint.h>
#include <halGpio.h>
#include "halUCS.h"
#include "halTimerB0.h"
#include "driverGeneral.h"
#include "driverAktorik.h"

//#define RUN_TESTS                   // auskommentieren für den Normalbetrieb

//#ifdef RUN_TESTS
//#include "testHalGeneral.h"
//#endif


extern volatile ButtonCom CCButton;

/**
 * main.c
 */


void main(void)
{
    halInit();
    driverInit();

//#ifdef RUN_TESTS
//    halInitTest();
//#endif

    while(1)
    {
        if (CCButton.active == 1)
        {
            switch (CCButton.button)
            {
                case 0:             // START_BUTTON
                    LCD_BL_TOGGLE;      // LCD EIN
                    break;
                case 1:             // STOP_BUTTON
                    LCD_BL_TOGGLE;     // LCD OFF
                    break;
            }

            CCButton.active = 0;   // Clear Flag
        }
    }
}
