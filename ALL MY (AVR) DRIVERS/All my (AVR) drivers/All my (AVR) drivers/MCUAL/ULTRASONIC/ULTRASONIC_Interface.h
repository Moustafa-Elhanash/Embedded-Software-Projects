/*
 * ULTRASONIC_Interface.h
 *
 * Created: 20/02/2024 03:32:23 م
 *  Author: win10
 */ 


#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

void ULTRASONIC_INIT(const ULTRASONIC_CONFIG_t *ultrasonic);

 
/* this function will return the distance */
uint16 ULTRASONIC_START_MEASURE(const ULTRASONIC_CONFIG_t *ultrasonic);



#endif /* ULTRASONIC_INTERFACE_H_ */