/*
 * Configuration.h
 *
 * Created: 20/11/2023 06:49:48 م
 *  Author: MOUSTAFA ELHANASH
 */ 


#ifndef GPIO_CONFIGURATION_H_
#define GPIO_CONFIGURATION_H_
#include "CPU_CONFIGURATIONS.h"
#include "All_Liberaries.h"


typedef enum{

	GPIO_PORTA=0,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD
	
	
}GPIO_PORT_t;

typedef enum{

GPIO_PIN0=0,
GPIO_PIN1,
GPIO_PIN2,
GPIO_PIN3,
GPIO_PIN4,
GPIO_PIN5,
GPIO_PIN6,
GPIO_PIN7
	
}GPIO_PIN_t;

typedef enum{

	GPIO_INPUT=0,
	GPIO_OUTPUT
	
	
}GPIO_STATUS_t;

typedef enum{

	GPIO_LOW=0,
	GPIO_HIGH
	
	
}GPIO_STATE_t;



#endif /* GPIO_CONFIGURATION_H_ */