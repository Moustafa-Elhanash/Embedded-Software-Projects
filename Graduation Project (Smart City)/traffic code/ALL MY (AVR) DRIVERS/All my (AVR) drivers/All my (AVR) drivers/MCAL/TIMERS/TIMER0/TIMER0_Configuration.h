/*
 * TIMER0_Configuration.h
 *
 * Created: 15/02/2024 10:19:47 م
 *  Author: MOUSTAFA
 */ 


#ifndef TIMER0_CONFIGURATION_H_
#define TIMER0_CONFIGURATION_H_

#include "CPU_CONFIGURATIONS.h"
#include "All_Liberaries.h"

/************************************************************************/
/*   Select the mode of the timer 0
                     Options : 
					          1- TIMER0_CTC_MODE
							  2- TIMER0_OVF_MODE
							  3- TIMER0_FASTPWM_MODE
							  4- TIMER0_PWM_MODE  */
/************************************************************************/
#define   TIMER0_CTC_MODE                      1
#define   TIMER0_OVF_MODE					   2
#define   TIMER0_FASTPWM_MODE				   3
#define   TIMER0_PWM_MODE		               4

#define   TIMER0_MODE   TIMER0_CTC_MODE

/************************************************************************/
/* Set the Required Prescaler
	 * Choose between
	 * - TIMER_NO_CLOCK_SOURCE
	 * - TIMER_NO_PRESCALER_FACTOR
	 * - TIMER_DIVISION_FACTOR_8
	 * - TIMER_DIVISION_FACTOR_64
	 * - TIMER_DIVISION_FACTOR_256
	 * - TIMER_DIVISION_FACTOR_1024
	 * - TIMER_T0_EXTERNAL_CLOCK_SOURCE_FALLING
	 * - TIMER_T0_EXTERNAL_CLOCK_SOURCE_RISING
	 */                                                                
/************************************************************************/
#define   TIMER_NO_CLOCK_SOURCE                      0
#define   TIMER_NO_PRESCALER_FACTOR                  1
#define   TIMER_DIVISION_FACTOR_8                    2
#define   TIMER_DIVISION_FACTOR_64                   3
#define   TIMER_DIVISION_FACTOR_256                  4
#define   TIMER_DIVISION_FACTOR_1024                 5
#define   TIMER_T0_EXTERNAL_CLOCK_SOURCE_FALLING     6
#define   TIMER_T0_EXTERNAL_CLOCK_SOURCE_RISING      7

#define   TIMER0_PRESCALER		TIMER_DIVISION_FACTOR_256
#define   TIMER_PRESCALER_MASK    0b11111000 

/************************************************************************/
/*    Compare Match Interrupt Enable & overflow interrupt
                     Options : 
					           1- ENABLE
							   2- DISABLE              */
/************************************************************************/
#define  ENABLE                      1
#define  DISABLE                     2
/************************************************************************/
/* Select pwm mode 
                     Options:
					         1- TIMER_OC0_DISCONNECTED
							 2- TIMER_CLR_ON_CTC_SET_ON_TOP
							 3- TIMER_SET_ON_CTC_CLR_ON_TOP           */
/************************************************************************/
#define  TIMER_OC0_DISCONNECTED             1
#define  TIMER_CLR_ON_CTC_SET_ON_TOP		2
#define  TIMER_SET_ON_CTC_CLR_ON_TOP		3

/************************************************************************/
/*  Set Compare Match Output Mode
		 * Choose between
		 * 1. TIMER_OC0_DISCONNECTED
		 * 2. TIMER_OC0_TOGGEL_ON_CTC
		 * 3. TIMER_OC0_CLEAR_ON_CTC
		 * 4. TIMER_OC0_SET_ON_CTC
		*/   
/************************************************************************/
#define    TIMER_OC0_DISCONNECTED            1
#define    TIMER_OC0_TOGGEL_ON_CTC			 2
#define    TIMER_OC0_CLEAR_ON_CTC			 3
#define    TIMER_OC0_SET_ON_CTC				 4
/************************************************************************/
/* Check mode type to apply its configurations        */
/************************************************************************/
#if TIMER0_MODE == TIMER0_OVF_MODE
     /*Set the Required Preload on TIMER0 Normal Mode*/
     #define   TIMER0_PRELOAD_VALUE               192
     /*Set Timer0 Overflow Interrupt */
     #define  TIMER0_OVERFLOW_INTERRUPT   ENABLE
#elif TIMER0_MODE == TIMER0_PWM_MODE
     /*Set the Required Compare Match Value on TIMER0 CTC Mode*/
     #define   TIMER0_CTC_VALUE                   250   
	 /* Select  pwm mode 
     Options:
		     1- TIMER_OC0_DISCONNECTED
			 2- TIMER_CLR_ON_CTC_SET_ON_TOP
			 3- TIMER_SET_ON_CTC_CLR_ON_TOP           */
	 #define  TIMER0_CTC_PWM_MODE           TIMER_SET_ON_CTC_CLR_ON_TOP
#elif TIMER0_MODE == TIMER0_CTC_MODE
     /*Set the Required Compare Match Value on TIMER0 CTC Mode*/
     #define   TIMER0_CTC_VALUE                   250 
	 /*Set Compare Match Output Mode*/
	 #define TIMER0_OC0_MODE				TIMER_OC0_DISCONNECTED
     /*Set Timer0 CTC Interrupt */
	 #define  TIMER0_CTC_INTERRUPT        ENABLE 
#elif TIMER0_MODE == TIMER0_FASTPWM_MODE
     /*Set the Required Compare Match Value on TIMER0 CTC Mode*/
	 #define   TIMER0_CTC_VALUE                   250 
	 /* Select  pwm mode 
     Options:
		     1- TIMER_OC0_DISCONNECTED
			 2- TIMER_CLR_ON_CTC_SET_ON_TOP
			 3- TIMER_SET_ON_CTC_CLR_ON_TOP      */
	 #define  TIMER0_CTC_PWM_MODE           TIMER_CLR_ON_CTC_SET_ON_TOP
#else
#error "Wrong TIMER0_MODE Configuration Option"
#endif


/************************************************************************/
/* interrupt types             */
/************************************************************************/
#define OV_INTURRUPT    1
#define CTC_INTERRUPT   2

#endif /* TIMER0_CONFIGURATION_H_ */