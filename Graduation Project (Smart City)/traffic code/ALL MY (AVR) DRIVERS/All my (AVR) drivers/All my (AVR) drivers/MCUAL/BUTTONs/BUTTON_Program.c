/*
 * BUTTON_Program.c
 *
 * Created: 23/11/2023 06:48:27 م
 *  Author: moustafa el-hanash
 */ 
#include "BUTTON_Private.h"

ERROR_STATE_t BUTTON_INIT(const BUTTON_CONFIG_t *button)
{
	ERROR_STATE_t error_state = F_NOK;
	
	if (NULL == button)
	{
		error_state = F_NULL_POINTER;
	}
	else
	{
		switch(button->ButtonConnection)
		{
			case PULL_UP:
			GPIO_SETPIN_DIRECTION(button->ButtonPort,button->ButtonPin,GPIO_INPUT);
			GPIO_SETPIN_PULLUP(button->ButtonPort,button->ButtonPin);
			error_state = F_OK;
			break;
			case PULL_DOWN:
			GPIO_SETPIN_DIRECTION(button->ButtonPort,button->ButtonPin,GPIO_INPUT);
			error_state = F_OK;
			break;
			default:
			error_state = F_NOK;
			break;
		}
		
	}
	return error_state;
}

uint8 BUTTON_READ(const BUTTON_CONFIG_t *button,ERROR_STATE_t  *error_state)
{
	uint8 ButtonRead=0;
	*error_state = F_NOK;
	
	if (NULL == button || NULL == error_state)
	{
		*error_state = F_NULL_POINTER;
	}
	else
	{
		
			
			 _delay_ms(10);
			 ButtonRead = GPIO_READPIN_VALUE(button->ButtonPort,button->ButtonPin);
			 *error_state = F_OK;
			
		
		
	}
	return ButtonRead;
}
