/*
 * TIMER0_Program.c
 *
 * Created: 15/02/2024 10:21:22 م
 *  Author: MOUSTAFA
 */ 

#include "TIMER0_Private.h"

static void(*TIMER0_PtrTo_Overflow_CallBack_Func)(void) = NULL;
static void(*TIMER0_PtrTo_CTC_CallBack_Func)(void) = NULL;

void TIMER0_INIT(void)
{
	/* Select the mode of timer0 */
#if TIMER0_MODE == TIMER0_CTC_MODE
      /*Initialize Waveform Generation Mode as CTC Mode*/
      CLR_BIT(TCCR0,TCCR0_WGM00);
      SET_BIT(TCCR0,TCCR0_WGM01);
      /*Set the Required CTC Value*/
      OCR0 = TIMER0_CTC_VALUE ;
      /*Timer0 Compare Match Interrupt Enable*/
      #if TIMER0_CTC_INTERRUPT == DISABLE
      CLR_BIT(TIMSK , TIMSK_OCIE0);
      #elif TIMER0_CTC_INTERRUPT == ENABLE
      SET_BIT(TIMSK , TIMSK_OCIE0);
      #else
      #error "Wrong TIMER0_CTC_INTERRUPT Configuration option"
      #endif

#elif TIMER0_MODE == TIMER0_OVF_MODE
      /*Initialize Waveform Generation Mode as Normal Mode*/
      CLR_BIT(TCCR0,TCCR0_WGM00);
      CLR_BIT(TCCR0,TCCR0_WGM01);
	  /*Set the Required Preload Value*/
	  TCNT0 = TIMER0_PRELOAD_VALUE;
	  /*Timer0 Overflow Interrupt Enable*/
	  #if TIMER0_OVERFLOW_INTERRUPT == DISABLE
	  CLR_BIT(TIMSK , TIMSK_TOIE0) ;
	  #elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
	  SET_BIT(TIMSK , TIMSK_TOIE0) ;
	  #else
	  #error "Wrong TIMER0_OVERFLOW_INTERRUPT Configuration option"
	  #endif
#elif TIMER0_MODE == TIMER0_FASTPWM_MODE
      /*Initialize Waveform Generation Mode as Fast PWM Mode*/
      SET_BIT(TCCR0,TCCR0_WGM00);
      SET_BIT(TCCR0,TCCR0_WGM01);
	  /*Set CTC Fast PWM MODE*/
	  #if TIMER0_CTC_PWM_MODE == TIMER_OC0_DISCONNECTED
	  CLR_BIT(TCCR0 , TCCR0_COM00);
	  CLR_BIT(TCCR0 , TCCR0_COM01);
	  #elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	  CLR_BIT(TCCR0 , TCCR0_COM00);
	  SET_BIT(TCCR0 , TCCR0_COM01);
	  #elif TIMER0_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	  SET_BIT(TCCR0 , TCCR0_COM00);
	  SET_BIT(TCCR0 , TCCR0_COM01);
	  #else
	  #error "Wrong TIMER0_CTC_PWM_MODE Configuration option"
	  #endif

	  /*Set the Required CTC Value*/
	  OCR0 = TIMER0_CTC_VALUE;
#elif TIMER0_MODE == TIMER0_PWM_MODE
      /*Initialize Waveform Generation Mode as PWM Mode*/
	  SET_BIT(TCCR0,TCCR0_WGM00);
      CLR_BIT(TCCR0,TCCR0_WGM01);
	  /*Set CTC PWM MODE*/
	  #if TIMER0_CTC_PWM_MODE == TIMER_OC0_DISCONNECTED
	  CLR_BIT(TCCR0 , TCCR0_COM00);
	  CLR_BIT(TCCR0 , TCCR0_COM01);
	  #elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	  CLR_BIT(TCCR0 , TCCR0_COM00);
	  SET_BIT(TCCR0 , TCCR0_COM01);
	  #elif TIMER0_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	  SET_BIT(TCCR0 , TCCR0_COM00);
	  SET_BIT(TCCR0 , TCCR0_COM01);
	  #else
	  #error "Wrong TIMER0_CTC_PWM_MODE Config"
	  #endif

	  /*Set the Required CTC Value*/
	  OCR0 = TIMER0_CTC_VALUE;
#else
#error "Wrong TIMER0_MODE option"
#endif

/*Set the Required Prescaler*/
TCCR0 &= TIMER_PRESCALER_MASK;
TCCR0 |= TIMER0_PRESCALER;

}
/* global interrupt enable required for this function */
ERROR_STATE_t TIMER0_SET_CALL_BACK(uint8 interrupt_type,void(*Ptr_To_CallBackFunc)(void))
{
	ERROR_STATE_t error_state = F_NOK;
	if (NULL == Ptr_To_CallBackFunc)
	{
		error_state = F_NULL_POINTER;
	} 
	else
	{
		if (interrupt_type == OV_INTURRUPT)
		{
			TIMER0_PtrTo_Overflow_CallBack_Func = Ptr_To_CallBackFunc;
			error_state = F_OK;
		} 
		else if (interrupt_type == CTC_INTERRUPT)
		{
			TIMER0_PtrTo_CTC_CallBack_Func = Ptr_To_CallBackFunc;
			error_state = F_OK;
		}
		else 
		{
			error_state = F_NOK;
		}
	}
	return error_state;
}

void TIMER0_SET_PRELOAD(uint8 Preload)
{
	TCNT0 = Preload;
}

void TIMER0_SET_CTC (uint8 CTC_val)
{
	OCR0 = CTC_val;
}

uint8 TIMER0_GetTimerCounterValue (void)
{
	return TCNT0;
}

void TIMER0_STOP_COUNTING(void)
{
	TCCR0 &= TIMER_PRESCALER_MASK;
	TCCR0 |= 0;

}
/*TIMER0 Normal (overflow) Mode ISR*/
void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
	if (TIMER0_PtrTo_Overflow_CallBack_Func != NULL)
	{
		TIMER0_PtrTo_Overflow_CallBack_Func();
	}
	else
	{
		/* nothing */
	}
}

/*TIMER0 CTC Mode ISR*/
void __vector_10(void)   __attribute__((signal));
void __vector_10(void)
{
	if (TIMER0_PtrTo_CTC_CallBack_Func != NULL)
	{
		TIMER0_PtrTo_CTC_CallBack_Func();
	}
	else
	{
		/* nothing */
	}
}
