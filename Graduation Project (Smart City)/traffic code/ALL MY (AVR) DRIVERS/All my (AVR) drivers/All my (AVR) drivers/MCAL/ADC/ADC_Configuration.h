/*
 * ADC_Configuration.h
 *
 * Created: 03/02/2024 08:54:06 م
 *  Author: MOUSTAFA
 */ 


#ifndef ADC_CONFIGURATION_H_
#define ADC_CONFIGURATION_H_

#include "CPU_CONFIGURATIONS.h"
#include "All_Liberaries.h"

/************************************************************************/
/*   Set the voltage reference for ADC   
        Options:
			     1- AREF internal vref tuned off                                          (INTERNAL_VREF)
			     2- AVCC with external capacitor at AREF pin                              (AVCC_AS_VREF)
				 3- internal 2.56v voltage reference with external capacitor at AREF pin  (INTERNAL_2_56V_VREF)  */
/************************************************************************/
#define INTERNAL_VREF            1
#define AVCC_AS_VREF             2
#define INTERNAL_2_56V_VREF      3

#define ADC_VOLTAGE_REF          AVCC_AS_VREF

/************************************************************************/
/*   Select adjust Result Type 
                        1- ADC_EIGHT_BIT       
						2- ADC_TEN_BIT         */
/************************************************************************/
#define  ADC_EIGHT_BIT     1
#define  ADC_TEN_BIT       2

#define  ADC_RESOLUTION    ADC_TEN_BIT

/************************************************************************/
/*   Select prescaler    (using musked bit method)
                        1- DEVISION_BY_2 
						2- DEVISION_BY_4
						3- DEVISION_BY_8 
						4- DEVISION_BY_16
						5- DEVISION_BY_32
						6- DEVISION_BY_64
						7- DEVISION_BY_128
						
						                               */
/************************************************************************/

#define   DEVISION_BY_2      1
#define	  DEVISION_BY_4		 2
#define	  DEVISION_BY_8		 3
#define	  DEVISION_BY_16	 4
#define	  DEVISION_BY_32	 5
#define	  DEVISION_BY_64	 6
#define	  DEVISION_BY_128	 7

#define   ADC_PRESCALER      DEVISION_BY_128

/************************************************************************/
/* set ADC_STATUS  
                        options:
						         1- ADC_ENABLED
								 2- ADC_DISABLED    */
/************************************************************************/

#define  ADC_ENABLED     1
#define  ADC_DISABLED    2

#define  ADC_STATUS      ADC_ENABLED


#define ADC_TIMEOUT      50000

/************************************************************************/
/* Busy flag config                                                                     */
/************************************************************************/

#define IDLE             0
#define BUSY             1
/************************************************************************/
/*     MOUSTAFA                                                                     */
/************************************************************************/
/* ADC_Asyn_Chain_Flag config  */
#define ASYN_CHAIN_ON    0
#define ASYN_CHAIN_OFF   1
/************************************************************************/
/*     MOUSTAFA                                                                     */
/************************************************************************/
#endif /* ADC_CONFIGURATION_H_ */