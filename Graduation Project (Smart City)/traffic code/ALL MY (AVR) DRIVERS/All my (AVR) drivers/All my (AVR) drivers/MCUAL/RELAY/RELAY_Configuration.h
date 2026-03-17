/*
 * RELAY_Configuration.h
 *
 * Created: 25/11/2023 06:25:44 م
 *  Author: MOUSTAFA
 */ 


#ifndef RELAY_CONFIGURATION_H_
#define RELAY_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

#define RELAY0_PORT     GPIO_PORTA
#define RELAY0_PIN      GPIO_PIN2

typedef struct{
	GPIO_PORT_t RelayPort;
	GPIO_PIN_t  RelayPin;
	
}RELAY_CONFIG_t;



#endif /* RELAY_CONFIGURATION_H_ */