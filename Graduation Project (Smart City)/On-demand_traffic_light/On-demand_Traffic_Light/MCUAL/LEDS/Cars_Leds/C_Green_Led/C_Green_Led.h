/*
 * C_Green_Led.h
 *
 * Created: 13/12/2022 08:39:59 م
 *  Author: Apple
 */ 


#ifndef C_GREEN_LED_H_
#define C_GREEN_LED_H_
//configuration
#include "configuration.h"

#define C_Green_Led DIO_PIN0
#define C_Green_Led_PRT DIO_PORTA
//functions prototypes
void C_Green_Led_Initialize(void);
void C_Green_Led_ON(void);
void C_Green_Led_OFF(void);
void C_Green_Led_TGL(void);




#endif /* C_GREEN_LED_H_ */