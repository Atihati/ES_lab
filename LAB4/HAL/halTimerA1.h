/*
 * halTimerA1.h
 *
 *  Created on: 24.10.2026
 *      Author: hrabo
 */

#ifndef HAL_HALTIMERA1_H_
#define HAL_HALTIMERA1_H_

#include <msp430.h>
#include <stdint.h>

#define ST_MIDDLE  3750
#define ST_LEFT    2500
#define ST_RIGHT   5000
// TODO: Oszi_measurment

void halTimerA1Init(void);
void halTimerA1SetSteering(unsigned int width);
void halTimerA1SetThrottle(unsigned int width);
void halTimerA1ResetPeriodCnt(void);
unsigned int halTimerA1GetPeriodCnt(void);



#endif /* HAL_HALTIMERA1_H_ */
