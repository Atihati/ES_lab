/*
 * halGpio.c
 *
 *  Created on: 05.10.2026
 *      Author: hrabo
 */

#include <msp430.h>
#include "halGpio.h"

void halGpioInit(void)
{
    // --- PORT 1 ---
    P1DIR = BIT0 | BIT1 | BIT2;
    P1OUT = START_BUTTON | STOP_BUTTON; // Pull-Up-Pegel setzen (High)
    P1REN = START_BUTTON | STOP_BUTTON; // Pull-Widerstand aktivieren

    // --- PORT 2 ---
    P2DIR = AUX_PIN_1 | AUX_PIN_2 | AUX_PIN_3 | AUX_PIN_4 | DEBUG_TXD;
    P2OUT = 0x00;
    P2REN = 0x00;

    // --- PORT 3 ---
    P3DIR = BIT0 | BIT1 | BIT5 | BIT6 | THROTTLE | STEERING | SMCLK | DISTANCE_FRONT_EN;
    P3OUT = 0x00;

    // --- PORT 4 ---
    P4DIR = BIT0 | BIT1 | BIT2;
    P4OUT = 0x00;

    // --- PORT 6 ---
    P6DIR = BIT5 | BIT6 | BIT7 | DISTANCE_LEFT_EN;
    P6OUT = 0x00;

    // --- PORT 7 ---
    P7DIR = 0xFF;
    P7OUT = 0x00;

    // --- PORT 8 ---
    P8DIR = LCD_BL | LCD_SPI_CS | UART_TXD_AUX | LCD_SPI_CLK | LCD_SPI_MOSI | LCD_DATACMD;
    P8OUT = 0x00;

    // --- PORT 9 ---
    P9DIR = BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | LCD_RESET | DISTANCE_RIGHT_EN;
    P9OUT = 0x00;
}
