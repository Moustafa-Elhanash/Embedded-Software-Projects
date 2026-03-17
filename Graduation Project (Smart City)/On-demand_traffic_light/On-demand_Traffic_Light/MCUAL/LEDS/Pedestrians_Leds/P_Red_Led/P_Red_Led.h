/*
 * P_Red_Led.h
 *
 * Created: 13/12/2022 08:44:05 م
 *  Author: Apple
 */ 


#ifndef P_RED_LED_H_
#define P_RED_LED_H_


//configuration
#include "configuration.h"

#define P_Red_Led DIO_PIN2
#define P_Red_Led_PRT DIO_PORTB
//functions prototypes
void P_Red_Led_Initialize(void);
void P_Red_Led_ON(void);
void P_Red_Led_OFF(void);
void P_Red_Led_TGL(void);


#endif /* P_RED_LED_H_ */