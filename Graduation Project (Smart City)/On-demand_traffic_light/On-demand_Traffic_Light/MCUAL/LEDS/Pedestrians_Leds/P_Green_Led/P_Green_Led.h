/*
 * P_Green_Led.h
 *
 * Created: 13/12/2022 08:44:30 م
 *  Author: Apple
 */ 


#ifndef P_GREEN_LED_H_
#define P_GREEN_LED_H_

//configuration
#include "configuration.h"

#define P_Green_Led DIO_PIN0
#define P_Green_Led_PRT DIO_PORTB
//functions prototypes
void P_Green_Led_Initialize(void);
void P_Green_Led_ON(void);
void P_Green_Led_OFF(void);
void P_Green_Led_TGL(void);




#endif /* P_GREEN_LED_H_ */