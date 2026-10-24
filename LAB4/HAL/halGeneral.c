/*
 * halGeneral.c
 *
 *  Created on: 05.10.2026
 *      Author: hrabo
 */
#include "halGeneral.h"
#include "halPMM.h"
#include "halGpio.h"
#include "halWdt.h"
#include "halUCS.h"
#include "halTimerB0.h"
#include "halTimerA1.h"


void halInit (void){
    halWdtInit();
    HAL_PMM_Init();
    halGpioInit();
    halUCSInit();
    //halTimerB0Init();
    halTimerA1Init();

}
