#include <msp430.h> 
#include <halGeneral.h>


/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	halInit();

	
	while(1){
	    // code block to be executed
	  }
}
