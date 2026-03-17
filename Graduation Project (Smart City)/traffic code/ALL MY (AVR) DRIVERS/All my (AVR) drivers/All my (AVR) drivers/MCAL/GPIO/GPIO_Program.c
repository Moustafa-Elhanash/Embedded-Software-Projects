
/*
 * Program.c
 *
 * Created: 20/11/2023 06:47:45 م
 *  Author: win10
 */ 


/* include peripherals files  (our layer) */

#include "GPIO_Private.h"


ERROR_STATE_t GPIO_SETPIN_DIRECTION(GPIO_PORT_t port , GPIO_PIN_t pin ,GPIO_STATUS_t status)
{
	ERROR_STATE_t error_state =F_NOK;
	switch(status)
	{
		case GPIO_OUTPUT:
		switch(port)
		{
			case GPIO_PORTA:
			SET_BIT(DDRA,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTB:
			SET_BIT(DDRB,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTC:
			SET_BIT(DDRC,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTD:
			SET_BIT(DDRD,pin);
			error_state =F_OK;
			break;
			default:
			error_state =F_NOK;
			break;
			
		}
	break;
	case GPIO_INPUT:
	    switch(port)
	    {
		    case GPIO_PORTA:
		    CLR_BIT(DDRA,pin);
		    error_state =F_OK;
		    break;
		    case GPIO_PORTB:
		    CLR_BIT(DDRB,pin);
		    error_state =F_OK;
		    break;
		    case GPIO_PORTC:
		    CLR_BIT(DDRC,pin);
		    error_state =F_OK;
		    break;
		    case GPIO_PORTD:
		    CLR_BIT(DDRD,pin);
		    error_state =F_OK;
		    break;
		    default:
		    error_state =F_NOK;
		    break;
		    
	    }
		break;
	}
	
	return error_state;
}
ERROR_STATE_t GPIO_SETPORT_DIRECTION(GPIO_PORT_t port , GPIO_STATUS_t status)
{
		ERROR_STATE_t error_state =F_NOK;
		
		switch(status)
		{
			case GPIO_OUTPUT:
			switch(port)
			{
				case GPIO_PORTA:
				DDRA=0b11111111;
				error_state =F_OK;
				break;
				case GPIO_PORTB:
				DDRB=0b11111111;
				error_state =F_OK;
				break;
				case GPIO_PORTC:
				DDRC=0b11111111;
				error_state =F_OK;
				break;
				case GPIO_PORTD:
				DDRD=0b11111111;
				error_state =F_OK;
				break;
				default:
				error_state =F_NOK;
				break;
			}
			break;
			case GPIO_INPUT:
			switch(port)
			{
				case GPIO_PORTA:
				DDRA=0;
				error_state =F_OK;
				break;
				case GPIO_PORTB:
				DDRB=0;
				error_state =F_OK;
				break;
				case GPIO_PORTC:
				DDRC=0;
				error_state =F_OK;
				break;
				case GPIO_PORTD:
				DDRD=0;
				error_state =F_OK;
				break;
				default:
				error_state =F_NOK;
				break;
			}
			break;
		}
		
		return error_state;
}

ERROR_STATE_t GPIO_SETPIN_VALUE(GPIO_PORT_t port , GPIO_PIN_t pin ,GPIO_STATE_t state)
{
	ERROR_STATE_t error_state =F_NOK;
	
	switch(state)
	{
		case GPIO_LOW:
		switch(port)
		{
			case GPIO_PORTA:
			CLR_BIT(PORTA,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTB:
			CLR_BIT(PORTB,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTC:
			CLR_BIT(PORTC,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTD:
			CLR_BIT(PORTD,pin);
			error_state =F_OK;
			break;
			default:
			error_state =F_NOK;
			break;
		}
		break;
		case GPIO_HIGH:
		switch(port)
		{
			case GPIO_PORTA:
			SET_BIT(PORTA,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTB:
			SET_BIT(PORTB,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTC:
			SET_BIT(PORTC,pin);
			error_state =F_OK;
			break;
			case GPIO_PORTD:
			SET_BIT(PORTD,pin);
			error_state =F_OK;
			break;
			default:
			error_state =F_NOK;
			break;
		}
		break;
	}
	return error_state;
}
ERROR_STATE_t GPIO_SETPORT_VALUE(GPIO_PORT_t port , GPIO_STATE_t state)
{
  ERROR_STATE_t error_state =F_NOK;
  switch(state)
  {
	  case GPIO_LOW:
	  switch(port)
	  {
		 case GPIO_PORTA:
		 PORTA = 0;
		 error_state =F_OK;
		 break;
		 case GPIO_PORTB:
		 PORTB = 0;
		 error_state =F_OK;
		 break;
		 case GPIO_PORTC:
		 PORTC = 0;
		 error_state =F_OK;
		 break;
		 case GPIO_PORTD:
		 PORTD = 0;
		 error_state =F_OK;
		 break;
		 default:
		 error_state =F_NOK;
		 break;
	  }
	  break;
	  case GPIO_HIGH:
	  switch(port)
	  {
		case GPIO_PORTA:
		PORTA = 0b11111111;
		error_state =F_OK;
		break;
		case GPIO_PORTB:
		PORTB = 0b11111111;
		error_state =F_OK;
		break;
		case GPIO_PORTC:
		PORTC = 0b11111111;
		error_state =F_OK;
		break;
		case GPIO_PORTD:
		PORTD = 0b11111111;
		error_state =F_OK;
		break;
		default:
		error_state =F_NOK;
		break;
	  }
	  break;
  }
  
  return error_state;
}
ERROR_STATE_t GPIO_WRITE_ON_PORT(GPIO_PORT_t port , uint8 port_value)
{
	ERROR_STATE_t error_state =F_NOK;
	switch(port)
	{
		case GPIO_PORTA:
		PORTA =port_value;
		error_state =F_OK;
		break;
		case GPIO_PORTB:
		PORTB =port_value;
		error_state =F_OK;
		break;
		case GPIO_PORTC:
		PORTC =port_value;
		error_state =F_OK;
		break;
		case GPIO_PORTD:
		PORTD =port_value;
		error_state =F_OK;
		break;
		default:
		error_state =F_NOK;
		break;
	}
	 return error_state;
}
ERROR_STATE_t GPIO_TOGPIN_VALUE(GPIO_PORT_t port ,GPIO_PIN_t pin)
{
	ERROR_STATE_t error_state =F_NOK;
	
	switch(port)
	{
		case GPIO_PORTA:
		TGL_BIT(PORTA,pin);
		error_state =F_OK;
		break;
		case GPIO_PORTB:
		TGL_BIT(PORTB,pin);
		error_state =F_OK;
		break;
		case GPIO_PORTC:
		TGL_BIT(PORTC,pin);
		error_state =F_OK;
		break;
		case GPIO_PORTD:
		TGL_BIT(PORTD,pin);
		error_state =F_OK;
		break;
		default:
		error_state =F_NOK;
		break;
	}
	return error_state;
}
ERROR_STATE_t GPIO_TOGPORT_VALUE(GPIO_PORT_t port)
{
	ERROR_STATE_t error_state =F_NOK;
	
	switch(port)
	{
		case GPIO_PORTA:
		PORTA = ~ PORTA;
		error_state =F_OK;
		break;
		case GPIO_PORTB:
		PORTB = ~ PORTB;
		error_state =F_OK;
		break;
		case GPIO_PORTC:
		PORTC = ~ PORTC;
		error_state =F_OK;
		break;
		case GPIO_PORTD:
		PORTD = ~ PORTD;
		error_state =F_OK;
		break;
		default:
		error_state =F_NOK;
		break;
	}
	return error_state;
}

uint8 GPIO_READPIN_VALUE(GPIO_PORT_t port ,GPIO_PIN_t pin)
{
	uint8 pin_value = 0;
	
	
		switch(port)
		{
			case GPIO_PORTA:
			pin_value=GET_BIT(PINA,pin);
			
			break;
			case GPIO_PORTB:
			pin_value=GET_BIT(PINB,pin);
			
			break;
			case GPIO_PORTC:
			pin_value=GET_BIT(PINC,pin);
			
			break;
			case GPIO_PORTD:
			pin_value=GET_BIT(PIND,pin);
			
			break;
			default:
		
			break;
		}
	
	
	return pin_value;
}
uint8 GPIO_READPORT_VALUE(GPIO_PORT_t port)
{
	uint8 port_value=0;
	

		switch(port)
		{
			case GPIO_PORTA:
			port_value=PINA;
		
			break;
			case GPIO_PORTB:
			port_value=PINB;
			
			break;
			case GPIO_PORTC:
			port_value=PINC;
			
			break;
			case GPIO_PORTD:
			port_value=PIND;
			
			break;
			default:
			
			break;
		}
	
	
	return port_value;
}

ERROR_STATE_t GPIO_SETPIN_PULLUP(GPIO_PORT_t port , GPIO_PIN_t pin)
{
	ERROR_STATE_t error_state =F_NOK;
	
	switch(port)
	{
		case GPIO_PORTA:
		SET_BIT(PORTA,pin);
		error_state =F_OK;
		break;
		case GPIO_PORTB:
		SET_BIT(PORTB,pin);
		error_state =F_OK;
		break;
		case GPIO_PORTC:
		SET_BIT(PORTC,pin);
		error_state =F_OK;
		break;
		case GPIO_PORTD:
		SET_BIT(PORTD,pin);
		error_state =F_OK;
		break;
		default:
		error_state =F_NOK;
		break;
	}
	return error_state;
}

