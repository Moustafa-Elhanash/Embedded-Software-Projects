/*
 * SERVO_Configuration.h
 *
 * Created: 01/02/2024 06:53:41 م
 *  Author: MOUSTAFA
 */ 


#ifndef SERVO_CONFIGURATION_H_
#define SERVO_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"



typedef struct{
	GPIO_PORT_t servoPort;
	GPIO_PIN_t servoPin;
	
	}SERVO_CONFIG_t;



#endif /* SERVO_CONFIGURATION_H_ */