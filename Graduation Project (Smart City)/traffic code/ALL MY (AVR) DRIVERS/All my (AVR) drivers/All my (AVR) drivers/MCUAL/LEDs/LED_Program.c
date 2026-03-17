/*
 * LED_Program.c
 *
 * Created: 21/11/2023 07:16:46 م
 *  Author: MOUSTAFA EL-HANASH
 */ 
/* include the needed libraries */
//#include "STD_Types.h"
////#include "BIT_MATH.h"
//#include "Error_Types.h"
/* include peripherals files (lower layer) */
//#include "GPIO_Private.h"
/* include module files (our layer )*/
#include "LED_Private.h"

ERROR_STATE_t LED_INIT(const LED_CONFIG_t *led)
{
	ERROR_STATE_t ErrorState=F_NOK;
 if (NULL == led)
 {
	ErrorState=F_NULL_POINTER; 
 }
 else
 {
	 GPIO_SETPIN_DIRECTION(led->LedPort,led->LedPin,GPIO_OUTPUT);
	 ErrorState=F_OK;
 }
 return ErrorState;
}
ERROR_STATE_t LED_ON(const LED_CONFIG_t *led)
{
	ERROR_STATE_t ErrorState=F_NOK;
	if (NULL == led)
	{
		ErrorState=F_NULL_POINTER;
	}
	else
	{
		switch(led->LedConnection)
		{
			case SINK_CONNECTION:
			GPIO_SETPIN_VALUE(led->LedPort,led->LedPin,GPIO_LOW);
			ErrorState=F_OK;
			break;
			case SOURCE_CONNECTION:
			GPIO_SETPIN_VALUE(led->LedPort,led->LedPin,GPIO_HIGH);
			ErrorState=F_OK;
			break;
			default:
			ErrorState=F_NOK;
			break;
		}
		
	}
	return ErrorState;
}
ERROR_STATE_t LED_OFF(const LED_CONFIG_t *led)
{
	ERROR_STATE_t ErrorState=F_NOK;
	if (NULL == led)
	{
		ErrorState=F_NULL_POINTER;
	}
	else
	{
		switch(led->LedConnection)
		{
			case SINK_CONNECTION:
			GPIO_SETPIN_VALUE(led->LedPort,led->LedPin,GPIO_HIGH);
			ErrorState=F_OK;
			break;
			case SOURCE_CONNECTION:
			GPIO_SETPIN_VALUE(led->LedPort,led->LedPin,GPIO_LOW);
			ErrorState=F_OK;
			break;
			default:
			ErrorState=F_NOK;
			break;
		}
		
	}
	return ErrorState;
}
ERROR_STATE_t LED_TGL(const LED_CONFIG_t *led)
{
	ERROR_STATE_t ErrorState=F_NOK;
	if (NULL == led)
	{
		ErrorState=F_NULL_POINTER;
	}
	else
	{
		GPIO_TOGPIN_VALUE(led->LedPort,led->LedPin);
		ErrorState=F_OK;
	}
	return ErrorState;
}

