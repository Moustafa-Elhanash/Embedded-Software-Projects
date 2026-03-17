/*
 * STEPPER_Program.c
 *
 * Created: 08/12/2023 06:27:55 م
 *  Author: moustafa
 
 */ 

#include "STEPPER_Private.h"

static const uint8 FullStep_Arr[4] = {0x09, 0x0C, 0x06, 0x03};

static const uint8 HalfStep_Arr[8] = {0x09, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01};

static const uint8 period = 10;   //100

ERROR_STATE_t STEPPER_INIT(const STEPPER_CONFIG_t *stepper)
{
	ERROR_STATE_t error_state=F_NOK;
	if (NULL == stepper)
	{
		error_state=F_NULL_POINTER;
	}
	else
	{
		//Define directions for pins
		GPIO_SETPIN_DIRECTION(stepper->stepper_port,stepper->A_Plus_Pin,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(stepper->stepper_port,stepper->A_Minus_Pin,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(stepper->stepper_port,stepper->B_Plus_Pin,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(stepper->stepper_port,stepper->B_Minus_Pin,GPIO_OUTPUT);
		
		ASSIGN_BIT(STEPPER,0,GET_BIT(0x09,0));
		ASSIGN_BIT(STEPPER,1,GET_BIT(0x09,1));
		ASSIGN_BIT(STEPPER,2,GET_BIT(0x09,2));
		ASSIGN_BIT(STEPPER,3,GET_BIT(0x09,3));
		
		error_state=F_OK;
	}
	
	
	
	return error_state;

}

ERROR_STATE_t STEPPER_ROTATE(const STEPPER_CONFIG_t *stepper)
{
	ERROR_STATE_t error_state=F_NOK;
	 uint8 counter = 0;
	if (NULL == stepper)
	{
		error_state=F_NULL_POINTER;
	}
	else
	{
        
         if(stepper->rotation_direction == Step_CW)
         {
	         if(stepper->step_type == Full_step)
	         {
		         for(counter = 0; counter < 4; counter++)
		         {
					 	ASSIGN_BIT(STEPPER,0,GET_BIT(FullStep_Arr[counter],0));
					 	ASSIGN_BIT(STEPPER,1,GET_BIT(FullStep_Arr[counter],1));
					 	ASSIGN_BIT(STEPPER,2,GET_BIT(FullStep_Arr[counter],2));
					 	ASSIGN_BIT(STEPPER,3,GET_BIT(FullStep_Arr[counter],3));
			        
			         _delay_ms(period);
		         }
	         }
	         else if(stepper->step_type == Half_step)
	         {
		         for(counter = 0; counter < 8; counter++)
		         {
					 ASSIGN_BIT(STEPPER,0,GET_BIT(HalfStep_Arr[counter],0));
					 ASSIGN_BIT(STEPPER,1,GET_BIT(HalfStep_Arr[counter],1));
					 ASSIGN_BIT(STEPPER,2,GET_BIT(HalfStep_Arr[counter],2));
					 ASSIGN_BIT(STEPPER,3,GET_BIT(HalfStep_Arr[counter],3));
			        
			         _delay_ms(period);
		         }
	         }
         }
         else if(stepper->rotation_direction == Step_CCW)
         {
	         if(stepper->step_type == Full_step)
	         {
		         for(counter = 3; counter >= 0; counter--)
		         {
			         	ASSIGN_BIT(STEPPER,0,GET_BIT(FullStep_Arr[counter],0));
			         	ASSIGN_BIT(STEPPER,1,GET_BIT(FullStep_Arr[counter],1));
			         	ASSIGN_BIT(STEPPER,2,GET_BIT(FullStep_Arr[counter],2));
			         	ASSIGN_BIT(STEPPER,3,GET_BIT(FullStep_Arr[counter],3));
			         _delay_ms(period);
		         }
	         }
	         else if(stepper->step_type == Half_step)
	         {
		         for(counter = 7; counter >= 0; counter--)
		         {
			         ASSIGN_BIT(STEPPER,0,GET_BIT(HalfStep_Arr[counter],0));
			         ASSIGN_BIT(STEPPER,1,GET_BIT(HalfStep_Arr[counter],1));
			         ASSIGN_BIT(STEPPER,2,GET_BIT(HalfStep_Arr[counter],2));
			         ASSIGN_BIT(STEPPER,3,GET_BIT(HalfStep_Arr[counter],3));
			         _delay_ms(period);
		         }
	         }
         }
         _delay_ms(1);     //125
		
		error_state=F_OK;
	}
	
	
	
	return error_state;

}

ERROR_STATE_t STEPPER_BRAKE(const STEPPER_CONFIG_t *stepper)   // to stop the stepper motor 
{
	ERROR_STATE_t error_state=F_NOK;
	if (NULL == stepper)
	{
		error_state=F_NULL_POINTER;
	}
	else
	{
		ASSIGN_BIT(STEPPER,0,GET_BIT(0x00,0));
		ASSIGN_BIT(STEPPER,1,GET_BIT(0x00,1));
		ASSIGN_BIT(STEPPER,2,GET_BIT(0x00,2));
		ASSIGN_BIT(STEPPER,3,GET_BIT(0x00,3));
		
		_delay_ms(250);
		
		ASSIGN_BIT(STEPPER,0,GET_BIT(0x09,0));
		ASSIGN_BIT(STEPPER,1,GET_BIT(0x09,1));
		ASSIGN_BIT(STEPPER,2,GET_BIT(0x09,2));
		ASSIGN_BIT(STEPPER,3,GET_BIT(0x09,3));

		error_state=F_OK;
	}
	
	
	
	return error_state;

}