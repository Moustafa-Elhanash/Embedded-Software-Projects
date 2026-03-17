/*
 * C_Yellow_Led.h
 *
 * Created: 13/12/2022 08:42:23 م
 *  Author: Apple
 */ 


#ifndef C_YELLOW_LED_H_
#define C_YELLOW_LED_H_

//configuration
#include "configuration.h"

#define C_Yellow_Led DIO_PIN1
#define C_Yellow_Led_PRT DIO_PORTA
//functions prototypes
void C_Yellow_Led_Initialize(void);
void C_Yellow_Led_ON(void);
void C_Yellow_Led_OFF(void);
void C_Yellow_Led_TGL(void);




#endif /* C_YELLOW_LED_H_ */