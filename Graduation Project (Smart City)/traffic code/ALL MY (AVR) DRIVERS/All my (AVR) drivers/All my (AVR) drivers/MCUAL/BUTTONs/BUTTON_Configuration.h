/*
 * BUTTON_Configuration.h
 *
 * Created: 23/11/2023 06:49:51 م
 *  Author:moustafa el hanash
 */ 


#ifndef BUTTON_CONFIGURATION_H_
#define BUTTON_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

/* button 0 */
#define BUTTON0_PRT     GPIO_PORTB      //kit GPIO_PORTB 
#define BUTTON0_PIN     GPIO_PIN2      //kit GPIO_PIN0 
/* button 1 */			
#define BUTTON1_PRT     GPIO_PORTD      //kit GPIO_PORTD 
#define BUTTON1_PIN     GPIO_PIN2	   //kit GPIO_PIN6 
/* button 2 */			
#define BUTTON2_PRT     GPIO_PORTD        //kit GPIO_PORTD 
#define BUTTON2_PIN     GPIO_PIN3		 //kit GPIO_PIN2 

typedef enum{

	PULL_UP,
	PULL_DOWN
}BUTTON_CONNECTION_t;

typedef struct{

	GPIO_PORT_t ButtonPort;
	GPIO_PIN_t ButtonPin;
	BUTTON_CONNECTION_t ButtonConnection;
}BUTTON_CONFIG_t;



#endif /* BUTTON_CONFIGURATION_H_ */