/*
 * driversSensors.h
 *
 *  Created on: 24.10.2026
 *      Author: hrabo
 */

#ifndef DRIVER_SENSORS_H_
#define DRIVER_SENSORS_H_

#define MM_PER_PULSE    5

void driverSensorsInit(void);
unsigned int getSpeed(void);
unsigned int getDistance(void);

#endif /* DRIVER_SENSORS_H_ */
