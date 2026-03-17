/*
 * DIO_interfacing.c
 *
 * Created: 9/20/2022 12:45:56 PM
 *  Author: User
 */ 
#include "DIO_Private.h"

void DIO_SETPIN_DIRECTION(DIO_PORTS port , DIO_PINS pin ,DIO_STATUS status)
{
	switch(status)
	{
		case DIO_INPUT:
		switch(port)
		{
			case DIO_PORTA:
			CLR_BIT(DDRA,pin);
			break;
			case DIO_PORTB:
			CLR_BIT(DDRB,pin);
			break;
			case DIO_PORTC:
			CLR_BIT(DDRC,pin);
			break;
			case DIO_PORTD:
			CLR_BIT(DDRD,pin);
			break;
		}
		break;
		case DIO_OUTPUT:
		switch(port)
		{
			case DIO_PORTA:
			SET_BIT(DDRA , pin);
			break;
			case DIO_PORTB:
			SET_BIT(DDRB ,pin);
			break;
			case DIO_PORTC:
			SET_BIT(DDRC , pin);
			break;
			case DIO_PORTD:
			SET_BIT(DDRD , pin);
			break;
		}
		break;
	}
	
}
void DIO_SETPIN_VALUE(DIO_PORTS port , DIO_PINS pins , DIO_STATE state)
{
	switch(state)
	{
		case DIO_LOW:
		switch(port)
		{
			case DIO_PORTA:
			CLR_BIT(PORTA,pins);
			break;
			case DIO_PORTB:
			CLR_BIT(PORTB,pins);
			break;
			case DIO_PORTC:
			CLR_BIT(PORTC,pins);
			break;
			case DIO_PORTD:
			CLR_BIT(PORTD,pins);
			break;
		}
		break;
		case DIO_HIGH:
		switch(port)
		{
			case DIO_PORTA:
			SET_BIT(PORTA , pins);
			break;
			case DIO_PORTB:
			SET_BIT(PORTB ,pins);
			break;
			case DIO_PORTC:
			SET_BIT(PORTC , pins);
			break;
			case DIO_PORTD:
			SET_BIT(PORTD , pins);
			break;
		}
		break;
	}
}
uint8_t DIO_READPIN_VALUE(DIO_PORTS port ,DIO_PINS pin)
{
	uint8_t value = 0 ;
	switch(port)
	{
		case DIO_PORTA:
		value = GET_BIT(PINA , pin);
		break;
		case DIO_PORTB:
		value = GET_BIT(PINB , pin);
		break;
		case DIO_PORTC:
		value = GET_BIT(PINC , pin);
		break;
		case DIO_PORTD:
		value = GET_BIT(PIND , pin);
		break;
		default:
		value = -1 ; 
		break;
	}
	
	return value ; 
	
}
void DIO_TOGPIN_VALUE(DIO_PORTS port ,DIO_PINS pin)
{
	switch(port)
	{
		case DIO_PORTA:
		TGL_BIT(PORTA , pin);
		break;
		case DIO_PORTB:
		TGL_BIT(PORTB ,pin);
		break;
		case DIO_PORTC:
		TGL_BIT(PORTC , pin);
		break;
		case DIO_PORTD:
		TGL_BIT(PORTD , pin);
		break;
	}
}
void DIO_SETPIN_PULLUP(DIO_PORTS port , DIO_PINS pin)
{
	switch(port)
	{
		case DIO_PORTA:
		SET_BIT(PORTA,pin);
		break;
		case DIO_PORTB:
		SET_BIT(PORTB,pin);
		break;
		case DIO_PORTC:
		SET_BIT(PORTC,pin);
		break;
		case DIO_PORTD:
		SET_BIT(PORTD,pin);
		break;
	}
}


void DIO_SETPORT_DIRECTION(DIO_PORTS port , DIO_STATUS status)
{
	switch (status)
	{
		case DIO_INPUT:
		switch(port)
		{
			case DIO_PORTA:
			DDRA = 0 ;
			break;
			
			case DIO_PORTB:
			DDRB = 0 ;
			break;
			
			case DIO_PORTC:
			DDRC = 0 ;
			break;
			
			case DIO_PORTD:
			DDRD = 0 ;
			break;
		}
		break;
		
		
		case DIO_OUTPUT:
		switch(port)
		{
			case DIO_PORTA:
			DDRA = 255 ;
			break;
			
			case DIO_PORTB:
			DDRB = 255 ;
			break;
			
			case DIO_PORTC:
			DDRC = 255 ;
			break;
			
			case DIO_PORTD:
			DDRD = 255 ;
			break;
		}
		break;
	}
}
void DIO_SETPORT_VALUE(DIO_PORTS port , DIO_STATE state)
{
	switch(state)
	{
		case DIO_LOW:
		switch(port)
		{
			case DIO_PORTA:
			PORTA=0;
			break;
			
			case DIO_PORTB:
			PORTB = 0;
			break;
			
			case DIO_PORTC:
			PORTC = 0;
			break;
			
			case DIO_PORTD:
			PORTD = 0 ;
			break;
		}
		break;
		
		case DIO_HIGH:
		switch(port)
		{
			case DIO_PORTA:
			PORTA=255;
			break;
			
			case DIO_PORTB:
			PORTB = 255;
			break;
			
			case DIO_PORTC:
			PORTC = 255;
			break;
			
			case DIO_PORTD:
			PORTD = 255 ;
			break;
		}
		break;
	}
}
uint8_t DIO_READPORT_VALUE(DIO_PORTS port)
{
	uint8_t value = 0 ;
	
	switch(port)
	{
		case DIO_PORTA:
		value = PINA;
		break;
		
		case DIO_PORTB:
		value = PINB;
		break;
		
		case DIO_PORTC:
		value = PINC;
		break;
		
		case DIO_PORTD:
		value = PIND;
		break;
	}
	return value ; 
}
void DIO_TOGPORT_VALUE(DIO_PORTS port)
{
	switch(port)
	{
		case DIO_PORTA:
		PORTA = ~ PORTA;
		break;
		
		case DIO_PORTB:
		PORTB = ~ PORTB;
		break;
		
		case DIO_PORTC:
		PORTC = ~ PORTC;
		break;
		
		case DIO_PORTD:
		PORTD = ~ PORTD;
		break;
	}
}


