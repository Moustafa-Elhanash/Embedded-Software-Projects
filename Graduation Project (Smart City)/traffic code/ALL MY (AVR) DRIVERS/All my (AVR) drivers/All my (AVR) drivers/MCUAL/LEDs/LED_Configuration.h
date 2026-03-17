/*
 * LED_Configuration.h
 *
 * Created: 21/11/2023 07:19:09 م
 *  Author: MOUSTAFA ELHANASH
 */ 


#ifndef LED_CONFIGURATION_H_
#define LED_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"



typedef enum{

	SINK_CONNECTION,
	SOURCE_CONNECTION
}LED_CONNECTION_t;

typedef struct{

GPIO_PORT_t LedPort;
GPIO_PIN_t LedPin;
LED_CONNECTION_t LedConnection;	
}LED_CONFIG_t;



#endif /* LED_CONFIGURATION_H_ */