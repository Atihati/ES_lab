/*
 * driverGeneral.c
 *
 *  Created on: 24.10.2026
 *      Author: hrabo
 */
#include "driverGeneral.h"
#include "driverAktorik.h"

void driverInit(void)
{
    driverSetSteering(0);
    driverESCinit();
}



