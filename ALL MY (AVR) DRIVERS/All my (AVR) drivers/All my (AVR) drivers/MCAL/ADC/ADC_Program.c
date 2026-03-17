/*
 * ADC_Program.c
 *
 * Created: 03/02/2024 08:53:02 م
 *  Author: Moustafa El-Hanash
 */ 
#include "ADC_Private.h"
/* Global pointer to hold the ADC Asynchronous digital result*/
static uint16 *ADC_Result = NULL;
	 
/* Global pointer to hold the ADC Asynchronous notification function result*/
static void(*ADC_ASYN_NotificationFun)(void) = NULL;

/* Busy flag */
static uint8 ADC_Busy_Flag;
/************************************************************************/
/*           MOUSTAFA                                                           */
/************************************************************************/
static uint8 ADC_Asyn_Chain_Flag = 0; 
/************************************************************************/
/*           MOUSTAFA                                                           */
/************************************************************************/
static uint8 ADC_Chain_Channel;

/************************************************************************/
/*           MOUSTAFA                                                            */
/************************************************************************/


void ADC_INIT(void)
{
	/* Set AREF as a voltage reference */
	#if ADC_VOLTAGE_REF == INTERNAL_VREF
	CLR_BIT(ADMUX,ADMUX_REFS1);
	CLR_BIT(ADMUX,ADMUX_REFS0);
	#elif ADC_VOLTAGE_REF == AVCC_AS_VREF
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
	#elif ADC_VOLTAGE_REF == INTERNAL_2_56V_VREF
	SET_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
	#else
	#error "Wrong ADC_VOLTAGE_REF option"
	#endif
	
	/* Activate the adjusted result for 8 or 10 bit resolution */
#if ADC_RESOLUTION == ADC_TEN_BIT
CLR_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_RESOLUTION == ADC_EIGHT_BIT
SET_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "Wrong ADC_RESOLUTION option"
#endif
    /* Set prescaler */
    ADCSRA &= 0b11111000;
    ADCSRA |= ADC_PRESCALER;
    /* enable ADC */
#if ADC_STATUS == ADC_ENABLED
SET_BIT(ADCSRA,ADCSRA_ADEN);
#elif ADC_STATUS == ADC_DISABLED
CLR_BIT(ADCSRA,ADCSRA_ADEN);
#else
#error "Wrong ADC_STATUS option"
#endif
}

ERROR_STATE_t ADC_START_CONVERSION_SYN(uint8 channel, uint16 *Result)
{
	ERROR_STATE_t error_state = F_NOK;
	uint32 counter = 0;
	if (NULL == Result)
	{
		error_state = F_NULL_POINTER;
	} 
	else
	{
		/* check ADC is idle */
		if (ADC_Busy_Flag == IDLE)
		{
			/* ADC is now busy */
			ADC_Busy_Flag = BUSY;
			/* Set the required channel */
			ADMUX &= 0b11100000;
			ADMUX |= channel;
			/* Start conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/* busy wait until conversion complete as long as the timeout period has not passed */
			while((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (counter != ADC_TIMEOUT))
			{
				counter++;
			}
			/* check about the reason why loop is finished */
			if (counter == ADC_TIMEOUT)
			{
				/* loop is finished due to timeout */
				error_state = F_TIMEOUT;
			}
			else
			{
				/* loop is finished due to complete flag is raised */
				/* clear the interrupt flag */
				SET_BIT(ADCSRA,ADCSRA_ADIF);
				/* return the data */
				#if ADC_RESOLUTION == ADC_TEN_BIT
				*Result = ADC_L_H;
				#elif ADC_RESOLUTION == ADC_EIGHT_BIT
				*Result = ADCH;
				#endif
				error_state = F_OK;
			}
			/* ADC is now idle */
			ADC_Busy_Flag = IDLE;
		} 
		else
		{
		  error_state = F_BUSY;	
		}
		
		

	}
	
	
	return error_state;
}
/* global interrupt must enabled before using this function*/
ERROR_STATE_t ADC_START_CONVERSION_ASYN(uint8 channel, uint16 *Result , void(*NotificationFun)(void))
{
	ADC_Asyn_Chain_Flag = ASYN_CHAIN_OFF; /////////////////////////////////////////////////////////////////////////////////
	ERROR_STATE_t error_state = F_NOK;
	if (NULL == Result || NULL == NotificationFun)
	{
		error_state = F_NULL_POINTER;
	} 
	else
	{
		/* check ADC is idle */
		if (ADC_Busy_Flag == IDLE)
		{
			/* ADC is now busy */
			ADC_Busy_Flag = BUSY;
			/* initialize the ADC result pointer globally */
			ADC_Result = Result;
			/* initialize the ADC notification function pointer globally */
			ADC_ASYN_NotificationFun = NotificationFun;
			
			/* Set the required channel */
			ADMUX &= 0b11100000;
			ADMUX |= channel;
			/* Start conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			
			/* ADC conversion complete interrupt enable */
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		
			error_state = F_OK;
		}
		else
		{
			error_state = F_BUSY;	
		}
		
	}
	return error_state;
}
/************************************************************************/
/*    moustafa                                                                     */
/************************************************************************/
/* global interrupt must enabled before using this function*/
ERROR_STATE_t ADC_START_CHAIN_CONVERSION_ASYN(uint8 channel, uint16 *Result , void(*NotificationFun)(void))
{
  ADC_Asyn_Chain_Flag = ASYN_CHAIN_ON; //////////////////////////////////////////////////////////////////////////////
  ERROR_STATE_t error_state = F_NOK;
  if (NULL == Result || NULL == NotificationFun)
  {
	  error_state = F_NULL_POINTER;
  }
  else
  {
	  /* check ADC is idle */
	  if (ADC_Busy_Flag == IDLE)
	  {
		  /* ADC is now busy */
		  ADC_Busy_Flag = BUSY;
		  /* initialize the ADC result pointer globally */
		  ADC_Result = Result;
		  
		  /* initialize the ADC notification function pointer globally */
		  ADC_ASYN_NotificationFun = NotificationFun;
		  /* initialize the ADC channel globally */
		  ADC_Chain_Channel = channel;
		  
		  /* Set the required channel */
		  ADMUX &= 0b11100000;
		  ADMUX |= channel;
		  /* Start conversion */
		  SET_BIT(ADCSRA,ADCSRA_ADSC);
		  
		  /* ADC conversion complete interrupt enable */
		  SET_BIT(ADCSRA,ADCSRA_ADIE);
		  
		  error_state = F_OK;
	  }
	  else
	  {
		  error_state = F_BUSY;
	  }
	  
  }
  
  return error_state;	
}
/************************************************************************/
/*    moustafa                                                                     */
/************************************************************************/
/* ADC ISR */
void __vector_16(void)   __attribute__((signal));
void __vector_16(void)
{
	/* apply the normal mode */
	if (ADC_Asyn_Chain_Flag == ASYN_CHAIN_OFF)
	{
		/* Read the result */
		#if ADC_RESOLUTION == ADC_TEN_BIT
		*ADC_Result = ADC_L_H;
		#elif ADC_RESOLUTION == ADC_EIGHT_BIT
		*ADC_Result = ADCH;
		#endif
		/* ADC conversion complete interrupt disable */
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
		/* ADC is now idle */
		ADC_Busy_Flag = IDLE;
	}
	/* apply the chain mode */ 
	else if (ADC_Asyn_Chain_Flag == ASYN_CHAIN_ON)
	{
			/* Read the result */
			#if ADC_RESOLUTION == ADC_TEN_BIT
			ADC_Result[ADC_Chain_Channel] = ADC_L_H;
			#elif ADC_RESOLUTION == ADC_EIGHT_BIT
			ADC_Result[ADC_Chain_Channel] = ADCH;
			#endif
			/* ADC conversion complete interrupt disable */
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
			/* ADC is now idle */
			ADC_Busy_Flag = IDLE;
			ADC_Chain_Channel = ADC_Chain_Channel+1;
			/* call the function again to achieve the asyn chain */
			if (ADC_Chain_Channel > 7)
			{
				/* nothing */
			}
			else
			{
				ADC_START_CHAIN_CONVERSION_ASYN(ADC_Chain_Channel,ADC_Result,ADC_ASYN_NotificationFun);
			}
			
			
	} 
	else
	{
		/* nothing */
	}
	
	/* Invoke the call back notification function */
	if (NULL == ADC_ASYN_NotificationFun)
	{
		/* nothing */
	} 
	else
	{
		ADC_ASYN_NotificationFun();
	}
}
