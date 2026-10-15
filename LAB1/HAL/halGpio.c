/*
 * halGpio.c
 *
 *  Created on: 05.10.2026
 *      Author: hrabo
 */
void halGpioInit(void){
    // PORT 1
    P1OUT = 0x00;
    P1DIR |= BIT3 | BIT4 | BIT5;

    // PORT 2
    P2OUT |= BIT1 | BIT7;
    P2IN =

}





// Setze Bit 3 (z. B. als Ausgang):
P1DIR |= RPM_SENSOR;

// Lösche Bit 3 (z. B. als Eingang):
P1DIR &= ~RPM_SENSOR;
