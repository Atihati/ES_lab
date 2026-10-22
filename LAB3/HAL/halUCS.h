/*
 * halUCS.h
 *
 *  Created on: 20.10.2026
 *      Author: hrabo
 */

#ifndef HAL_HALUCS_H_
#define HAL_HALUCS_H_

#include <msp430.h>

#define XTAL_FREQU  20000000    // 20 MHz
#define MCLK_FREQU  20000000    // 20 MHz
#define SMCLK_FREQU 2500000     // 2.5 MHz

void halUCSInit(void);
void delayMsBlocked(unsigned int ms);

#endif

