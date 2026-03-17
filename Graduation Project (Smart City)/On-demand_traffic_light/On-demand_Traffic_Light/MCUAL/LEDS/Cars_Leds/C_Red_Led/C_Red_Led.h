/*
 * C_Red_Led.h
 *
 * Created: 13/12/2022 08:41:42 م
 *  Author: Apple
 */ 


#ifndef C_RED_LED_H_
#define C_RED_LED_H_

//configuration
#include "configuration.h"

#define C_Red_Led DIO_PIN2
#define C_Red_Led_PRT DIO_PORTA
//functions prototypes
void C_Red_Led_Initialize(void);
void C_Red_Led_ON(void);
void C_Red_Led_OFF(void);
void C_Red_Led_TGL(void);




#endif /* C_RED_LED_H_ */