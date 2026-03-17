/*
 * KEYPAD_Configuration.h
 *
 * Created: 05/12/2023 03:56:07 م
 *  Author: MOustafa
 */ 


#ifndef KEYPAD_CONFIGURATION_H_
#define KEYPAD_CONFIGURATION_H_


#include "ALL_LOW_LAYER_FILES.h"

#define  KEYPAD_PORT     GPIO_PORTC

/* define row pins (input)*/
#define  KEYPAD_ROW0_PIN     GPIO_PIN0
#define  KEYPAD_ROW1_PIN     GPIO_PIN1
#define  KEYPAD_ROW2_PIN     GPIO_PIN2
#define  KEYPAD_ROW3_PIN     GPIO_PIN3

/* define column pins (output) */

#define  KEYPAD_COLUMN0_PIN     GPIO_PIN4
#define  KEYPAD_COLUMN1_PIN     GPIO_PIN5
#define  KEYPAD_COLUMN2_PIN     GPIO_PIN6
#define  KEYPAD_COLUMN3_PIN     GPIO_PIN7

/*  define button values */

#define  KEYPAD_BUTTON_VALUES    {{'1','2','3','A'},{'5','6','7','B'},{'9','C','D','E'},{'F','G','H','I'}}
	
	
	
#define  NUMBER_OF_ROWS      4
#define  NUMBER_OF_COLUMNS   4

#define  KEYPAD_NOT_PRESSED  0xff

#endif /* KEYPAD_CONFIGURATION_H_ */