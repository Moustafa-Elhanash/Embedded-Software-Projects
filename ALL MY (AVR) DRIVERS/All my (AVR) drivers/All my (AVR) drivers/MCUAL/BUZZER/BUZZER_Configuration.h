/*
 * BUZZER_Configuration.h
 *
 * Created: 25/11/2023 04:19:43 م
 *  Author: MOUSTAFA
 */ 


#ifndef BUZZER_CONFIGURATION_H_
#define BUZZER_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

#define BUZZER0_PORT     GPIO_PORTA
#define BUZZER0_PIN      GPIO_PIN3

typedef struct{
	GPIO_PORT_t BuzzerPort;
	GPIO_PIN_t  BuzzerPin;
	
	}BUZZER_CONFIG_t;



#endif /* BUZZER_CONFIGURATION_H_ */