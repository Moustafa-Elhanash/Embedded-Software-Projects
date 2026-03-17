/*
 * EXT_INTERRUPT_Program.c
 *
 * Created: 11/12/2023 07:11:28 م
 *  Author: moustafa
 */ 
/* Array of global pointers to function to hold ISR Addresses */
static void (*Array_of_ptr_to_callBackFunction[3])(void)={0};
#include "EXT_INTERRUPT_Private.h"

void EXT_INTERRUPT_INIT(void)
{
	/* Set INT0 sense control */
#if EXT_INT0_SENSE == LOW_LEVEL
CLR_BIT(MCUCR,MCUCR_ISC00);
CLR_BIT(MCUCR,MCUCR_ISC01);

#elif EXT_INT0_SENSE == ON_CHANGE
SET_BIT(MCUCR,MCUCR_ISC00);
CLR_BIT(MCUCR,MCUCR_ISC01);

#elif EXT_INT0_SENSE == FALLING_EDGE
CLR_BIT(MCUCR,MCUCR_ISC00);
SET_BIT(MCUCR,MCUCR_ISC01);

#elif EXT_INT0_SENSE == RISING_EDGE
SET_BIT(MCUCR,MCUCR_ISC00);
SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "Wrong EXT_INT0_SENSE option"
#endif
/* Set INT1 sense control */
#if EXT_INT1_SENSE == LOW_LEVEL
CLR_BIT(MCUCR,MCUCR_ISC10);
CLR_BIT(MCUCR,MCUCR_ISC11);

#elif EXT_INT1_SENSE == ON_CHANGE
SET_BIT(MCUCR,MCUCR_ISC10);
CLR_BIT(MCUCR,MCUCR_ISC11);

#elif EXT_INT1_SENSE == FALLING_EDGE
CLR_BIT(MCUCR,MCUCR_ISC10);
SET_BIT(MCUCR,MCUCR_ISC11);

#elif EXT_INT1_SENSE == RISING_EDGE
SET_BIT(MCUCR,MCUCR_ISC10);
SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error "Wrong EXT_INT1_SENSE option"
#endif
/* Set INT2 sense control */

#if EXT_INT2_SENSE == FALLING_EDGE
CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif EXT_INT2_SENSE == RISING_EDGE
SET_BIT(MCUCSR,MCUCSR_ISC2);

#else
#error "Wrong EXT_INT2_SENSE option"
#endif
/* Set INT0 state control */
#if EXT_INT0_STATE == ENABLED
SET_BIT(GICR,GICR_INT0);

#elif EXT_INT0_STATE == DISABLED
CLR_BIT(GICR,GICR_INT0);
#else
#error "Wrong EXT_INT0_STATE option"
#endif

/* Set INT1 state control */
#if EXT_INT1_STATE == ENABLED
SET_BIT(GICR,GICR_INT1);

#elif EXT_INT1_STATE == DISABLED
CLR_BIT(GICR,GICR_INT1);
#else
#error "Wrong EXT_INT1_STATE option"
#endif

/* Set INT2 state control */
#if EXT_INT2_STATE == ENABLED
SET_BIT(GICR,GICR_INT2);

#elif EXT_INT2_STATE == DISABLED
CLR_BIT(GICR,GICR_INT2);
#else
#error "Wrong EXT_INT2_STATE option"
#endif
	
}

void EXT_ENABLE_GLOBAL(void)
{
	SET_BIT(SREG,SREG_I);
	/*volatile __asm ("SEI");  */   //inline assembly syntax in gcc toolchain
}

void EXT_DISABLE_GLOBAL(void)
{
	CLR_BIT(SREG,SREG_I);
	/*volatile __asm ("CEI"); */    //inline assembly syntax in gcc toolchain
}

/*  to solve this function bug you must replace all #if  by normal if syntax 
ERROR_STATE_t EXT_SET_SENSE_CONTROl(uint8 int_num,uint8 sense)
{
	ERROR_STATE_t error_state=F_NOK;
	switch(int_num)
	{
		case 0:
		/ * change INT0 sense control * /
		#if sense == LOW_LEVEL
		CLR_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
		error_state=F_OK;

		#elif sense == ON_CHANGE
		SET_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
		error_state=F_OK;

		#elif sense == FALLING_EDGE
		CLR_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
		error_state=F_OK;

		#elif sense == RISING_EDGE
		SET_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
		error_state=F_OK;

		#else
		error_state=F_NOK;
		#endif
		break;
		
		case 1:
		/ * change INT1 sense control * /
		#if sense == LOW_LEVEL
		CLR_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);
		error_state=F_OK;

		#elif sense == ON_CHANGE
		SET_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);
		error_state=F_OK;

		#elif sense == FALLING_EDGE
		CLR_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);
		error_state=F_OK;

		#elif sense == RISING_EDGE
		SET_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);
		error_state=F_OK;

		#else
		error_state=F_NOK;
		#endif
		break;
		
		case 2:
		/ * change INT2 sense control * /

		#if sense == FALLING_EDGE
		CLR_BIT(MCUCSR,MCUCSR_ISC2);
		error_state=F_OK;

		#elif sense == RISING_EDGE
		SET_BIT(MCUCSR,MCUCSR_ISC2);
		error_state=F_OK;

		#else
		error_state=F_NOK;
		#endif
		break;
		default:
		error_state=F_NOK;
		break;
	}
	return error_state;
}   */
ERROR_STATE_t EXT_SET_CALL_BACK(uint8 int_number,void(*ptr_to_callBackFunction)(void))
{
	ERROR_STATE_t error_state =F_NOK;
	if (NULL== ptr_to_callBackFunction)
	{
		error_state =F_NULL_POINTER;
	} 
	else
	{
		if (int_number < 3)
		{
			Array_of_ptr_to_callBackFunction[int_number]=ptr_to_callBackFunction;
			error_state = F_OK;
		} 
		else
		{
			error_state = F_NOK;
		}
	}
	
	return error_state;
}
/* ISR of INT0*/

void __vector_1(void)   __attribute__((signal));
void __vector_1(void)
{
	
	if (Array_of_ptr_to_callBackFunction[INT0] != NULL)
	{
		Array_of_ptr_to_callBackFunction[INT0]();
	} 
	else
	{
		/* nothing */
	}
	
}

/* ISR of INT1*/

void __vector_2(void)   __attribute__((signal));
void __vector_2(void)
{
	if (Array_of_ptr_to_callBackFunction[INT1] != NULL)
	{
		Array_of_ptr_to_callBackFunction[INT1]();
	}
	else
	{
		/* nothing */
	}
	
}

/* ISR of INT2*/

void __vector_3(void)   __attribute__((signal));
void __vector_3(void)
{
	
	if (Array_of_ptr_to_callBackFunction[INT2] != NULL)
	{
		Array_of_ptr_to_callBackFunction[INT2]();
	}
	else
	{
		/* nothing */
	}
}
