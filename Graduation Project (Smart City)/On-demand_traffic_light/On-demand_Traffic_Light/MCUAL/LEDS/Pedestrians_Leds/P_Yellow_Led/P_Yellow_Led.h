/*
 * P_Yellow_Led.h
 *
 * Created: 13/12/2022 08:43:24 م
 *  Author: Apple
 */ 


#ifndef P_YELLOW_LED_H_
#define P_YELLOW_LED_H_

//configuration
#include "configuration.h"

#define P_Yellow_Led DIO_PIN1
#define P_Yellow_Led_PRT DIO_PORTB
//functions prototypes
void P_Yellow_Led_Initialize(void);
void P_Yellow_Led_ON(void);
void P_Yellow_Led_OFF(void);
void P_Yellow_Led_TGL(void);




#endif /* P_YELLOW_LED_H_ */