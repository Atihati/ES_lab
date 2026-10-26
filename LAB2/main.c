#include <msp430.h> 
#include <halGeneral.h>
#include <stdint.h>
#include <halGpio.h>

#define RUN_TESTS                   // auskommentieren für den Normalbetrieb

#ifdef RUN_TESTS
#include "testHalGeneral.h"
#endif


extern volatile ButtonCom CCButton;

/**
 * main.c
 */

uint16_t int_a = 16972;
uint16_t int_b = 23546;
uint16_t int_c;
uint32_t int_result;

float float_a = 33.417;
float float_b = 22.008;
float float_c;

void main(void)
{
    halInit();

#ifdef RUN_TESTS
    halInitTest();
#endif

    while(1)
    {
        if (CCButton.active == 1)
                {
                    switch (CCButton.button)
                    {
                        case START_BUTTON:       // Nutzt nun das korrekte Makro aus der Header-Datei
                            LCD_BACKLIGHT_ON;    // LCD EIN
                            break;
                        case STOP_BUTTON:        // Nutzt nun das korrekte Makro aus der Header-Datei
                            LCD_BACKLIGHT_OFF;   // LCD OFF
                            break;
                    }

                    CCButton.active = 0;   // Clear Flag
                }
    }
}
