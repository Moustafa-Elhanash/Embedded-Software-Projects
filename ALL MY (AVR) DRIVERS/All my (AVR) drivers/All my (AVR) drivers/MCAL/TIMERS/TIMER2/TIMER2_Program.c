/*
 * TIMER2_Program.c
 *
 * Created: 19/02/2024 07:12:01 م
 *  Author: moustafa
 */ 
#include "TIMER2_Private.h"

static void(*TIMER2_PtrTo_Overflow_CallBack_Func)(void) = NULL;
static void(*TIMER2_PtrTo_CTC_CallBack_Func)(void) = NULL;


void TIMER2_INIT(void)
{
	/* Select the mode of timer2 */
#if TIMER2_MODE == TIMER2_CTC_MODE
	/*Initialize Waveform Generation Mode as CTC Mode*/
	CLR_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);
	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VALUE ;
	/*Timer2 Compare Match Interrupt Enable*/
	#if TIMER2_CTC_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_OCIE2);
	#elif TIMER2_CTC_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_OCIE2);
	#else
	#error "Wrong TIMER2_CTC_INTERRUPT Configuration option"
	#endif

#elif TIMER2_MODE == TIMER2_OVF_MODE
	/*Initialize Waveform Generation Mode as Normal Mode*/
	CLR_BIT(TCCR2,TCCR2_WGM20);
	CLR_BIT(TCCR2,TCCR2_WGM21);
	/*Set the Required Preload Value*/
	TCNT2 = TIMER2_PRELOAD_VALUE;
	/*Timer2 Overflow Interrupt Enable*/
	#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
	CLR_BIT(TIMSK , TIMSK_TOIE2) ;
	#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK , TIMSK_TOIE2) ;
	#else
	#error "Wrong TIMER2_OVERFLOW_INTERRUPT Configuration option"
	#endif
#elif TIMER2_MODE == TIMER2_FASTPWM_MODE
	/*Initialize Waveform Generation Mode as Fast PWM Mode*/
	SET_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);
	/*Set CTC Fast PWM MODE*/
	#if TIMER2_CTC_PWM_MODE == TIMER_OC2_DISCONNECTED
	CLR_BIT(TCCR2 , TCCR2_COM20);
	CLR_BIT(TCCR2 , TCCR2_COM21);
	#elif TIMER2_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR2 , TCCR2_COM20);
	SET_BIT(TCCR2 , TCCR2_COM21);
	#elif TIMER2_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR2 , TCCR2_COM20);
	SET_BIT(TCCR2 , TCCR2_COM21);
	#else
	#error "Wrong TIMER2_CTC_PWM_MODE Configuration option"
	#endif

	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VALUE;
#elif TIMER2_MODE == TIMER2_PWM_MODE
	/*Initialize Waveform Generation Mode as PWM Mode*/
	SET_BIT(TCCR2,TCCR2_WGM20);
	CLR_BIT(TCCR2,TCCR2_WGM21);
	/*Set CTC PWM MODE*/
	#if TIMER2_CTC_PWM_MODE == TIMER_OC2_DISCONNECTED
	CLR_BIT(TCCR2 , TCCR2_COM20);
	CLR_BIT(TCCR2 , TCCR2_COM21);
	#elif TIMER2_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR2 , TCCR2_COM20);
	SET_BIT(TCCR2 , TCCR2_COM21);
	#elif TIMER2_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR2 , TCCR2_COM20);
	SET_BIT(TCCR2 , TCCR2_COM21);
	#else
	#error "Wrong TIMER2_CTC_PWM_MODE Config"
	#endif

	/*Set the Required CTC Value*/
	OCR2 = TIMER2_CTC_VALUE;
#else
#error "Wrong TIMER2_MODE option"
#endif

	/*Set the Required Prescaler*/
	TCCR2 &= TIMER_PRESCALER_MASK;
	TCCR2 |= TIMER2_PRESCALER;

}

ERROR_STATE_t TIMER2_SET_CALL_BACK(uint8 interrupt_type,void(*Ptr_To_CallBackFunc)(void))
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
			TIMER2_PtrTo_Overflow_CallBack_Func = Ptr_To_CallBackFunc;
			error_state = F_OK;
		}
		else if (interrupt_type == CTC_INTERRUPT)
		{
			TIMER2_PtrTo_CTC_CallBack_Func = Ptr_To_CallBackFunc;
			error_state = F_OK;
		}
		else
		{
			error_state = F_NOK;
		}
	}
	return error_state;
}

void TIMER2_SET_PRELOAD(uint8 Preload)
{
	TCNT2 = Preload;
}

void TIMER2_SET_CTC (uint8 CTC_val)
{
	OCR2 = CTC_val;
}

uint8 TIMER2_GetTimerCounterValue (void)
{
	return TCNT2 ;
}

void TIMER2_STOP_COUNTING(void)
{
	TCCR2 &= TIMER_PRESCALER_MASK;
	TCCR2 |= 0;
}

/*TIMER2 Normal (overflow) Mode ISR*/
void __vector_5(void)   __attribute__((signal));
void __vector_5(void)
{
	if (TIMER2_PtrTo_Overflow_CallBack_Func != NULL)
	{
		TIMER2_PtrTo_Overflow_CallBack_Func();
	}
	else
	{
		/* nothing */
	}
}

/*TIMER2 CTC Mode ISR*/
void __vector_4(void)   __attribute__((signal));
void __vector_4(void)
{
	if (TIMER2_PtrTo_CTC_CallBack_Func != NULL)
	{
		TIMER2_PtrTo_CTC_CallBack_Func();
	}
	else
	{
		/* nothing */
	}
}
