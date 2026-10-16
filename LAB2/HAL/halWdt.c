/*
 * halWdt.c
 *
 *  Created on: 05.10.2026
 *      Author: hrabo
 */
# include <halWdt.h>
# include <msp430.h>

void halWdtInit(void){
    WDTCTL = WDTPW | WDTHOLD;
}


