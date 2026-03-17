/*
 * Button.h
 *
 * Created: 13/12/2022 09:41:54 م
 *  Author: Apple
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "configuration.h"

#define Button_prt DIO_PORTD
#define Button_pin DIO_PIN2


void Button_Initialization(void);
uint8_t Button_Read(void);



#endif /* BUTTON_H_ */