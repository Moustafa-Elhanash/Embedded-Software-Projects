/*
 * ULTRASONIC_Configuration.h
 *
 * Created: 20/02/2024 03:32:01 م
 *  Author: win10
 */ 


#ifndef ULTRASONIC_CONFIGURATION_H_
#define ULTRASONIC_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

typedef struct{

	GPIO_PORT_t ultrasonic_Port;
	GPIO_PIN_t ultrasonic_trig_Pin;
//	GPIO_PIN_t ultrasonic_echo_Pin;

}ULTRASONIC_CONFIG_t;



#endif /* ULTRASONIC_CONFIGURATION_H_ */