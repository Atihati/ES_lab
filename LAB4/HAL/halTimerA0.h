/*
 * halTimerA0.h
 *
 *  Created on: 26.10.2026
 *      Author: hrabo
 */

#ifndef HAL_HALTIMERA0_H_
#define HAL_HALTIMERA0_H_


void halTimerA0Init(void);
unsigned int halTimerA0GetPulseCnt(void);
void halTimerA0ResetPulseCnt(void);

#endif /* HAL_HALTIMERA0_H_ */
