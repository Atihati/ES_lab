/*
 * halGpio.c
 *
 *  Created on: 05.10.2026
 *      Author: hrabo
 */

#include <msp430.h>
#include "halGpio.h"
volatile ButtonCom CCButton;

void halGpioInit(void)
{
    // --- PORT 1 ---
    P1DIR = BIT0 | BIT1 | BIT2;
    P1OUT = START_BUTTON | STOP_BUTTON; // Pull-Up-Pegel setzen (High)
    P1REN = START_BUTTON | STOP_BUTTON; // Pull-Widerstand aktivieren

    P1IES |= START_BUTTON | STOP_BUTTON;
    P1IFG &= ~(START_BUTTON | STOP_BUTTON); // Clear specific flags properly
    P1IE  |= START_BUTTON | STOP_BUTTON;

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

    //***********************************

    P1IFG &= 0x00;
    __enable_interrupt();
}

// Interrupts

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
    CCButton.active = 1;

    if (P1IFG & START_BUTTON)
    {
        CCButton.button = START_BUTTON; // Übergibt den Bitmasken-Wert (z.B. 64) für den Test
        P1IFG &= ~START_BUTTON;         // Flag sauber einzeln löschen
    }
    else if (P1IFG & STOP_BUTTON)
    {
        CCButton.button = STOP_BUTTON;  // Übergibt den Bitmasken-Wert (z.B. 128) für den Test
        P1IFG &= ~STOP_BUTTON;          // Flag sauber einzeln löschen
    }
    else
    {
        CCButton.button = 2;
        P1IFG &= 0x00;
    }
}
