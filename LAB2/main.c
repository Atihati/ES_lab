#include <msp430.h> 
#include <halGeneral.h>
#include <stdint.h>
#include <halGpio.h>

extern volatile ButtonCom CCbutton;

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
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    halInit();

    while(1)
    {
        if (CCbutton.active == 1)
        {
            switch (CCbutton.button)
            {
                case 0:             // START_BUTTON
                    LCD_BACKLIGHT_ON;      // LCD EIN
                    break;
                case 1:             // STOP_BUTTON
                    LCD_BACKLIGHT_OFF;     // LCD OFF
                    break;
            }

            CCbutton.active = 0;   // Clear Flag
        }
    }
}
