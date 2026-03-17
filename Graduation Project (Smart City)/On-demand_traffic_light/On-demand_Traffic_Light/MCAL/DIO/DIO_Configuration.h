/*
 * DIO_Configuration.h
 *
 * Created: 9/20/2022 12:45:37 PM
 *  Author: User
 */ 


#ifndef DIO_CONFIGURATION_H_
#define DIO_CONFIGURATION_H_

#include "configuration.h"
#include "AVR_Address.h"


typedef enum
{
	DIO_PORTA=0,
	DIO_PORTB=1,
	DIO_PORTC=2,
	DIO_PORTD=3
}DIO_PORTS;

typedef enum
{
	DIO_PIN0=0,
	DIO_PIN1=1,
	DIO_PIN2=2,
	DIO_PIN3=3,
	DIO_PIN4=4,
	DIO_PIN5=5,
	DIO_PIN6=6,
	DIO_PIN7=7

	}DIO_PINS;
	
	
	typedef enum
	{
		DIO_INPUT=1,
		DIO_OUTPUT=0
	}DIO_STATUS;
	
	typedef enum
	{
		DIO_HIGH=1,
		DIO_LOW=0
	}DIO_STATE;
	
	



#endif /* DIO_CONFIGURATION_H_ */