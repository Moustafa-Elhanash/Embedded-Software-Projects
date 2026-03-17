/*
 * EXT_INTERRUPT_Configuration.h
 *
 * Created: 11/12/2023 07:21:39 م
 *  Author: moustafa
 */ 


#ifndef EXT_INTERRUPT_CONFIGURATION_H_
#define EXT_INTERRUPT_CONFIGURATION_H_

#include "CPU_CONFIGURATIONS.h"
#include "All_Liberaries.h"
/* interrupt number */
#define INT0            0
#define INT1            1
#define INT2            2

/* Interrupt sense types */
#define LOW_LEVEL       1
#define ON_CHANGE       2
#define FALLING_EDGE    3
#define RISING_EDGE     4
/* interrupt pie state */
#define ENABLED         1
#define DISABLED        2

/************************************************************************/
/*          EXT_INT0_SENSE                                                               */
/************************************************************************/
/*
  Options:   
            1- LOW_LEVEL
			2- ON_CHANGE
			3- FALLING_EDGE
			4- RISING_EDGE
*/
#define EXT_INT0_SENSE       RISING_EDGE
/************************************************************************/
/*         EXT_INT1_SENSE                                                                  */
/************************************************************************/
/*
  Options:   
            1- LOW_LEVEL
			2- ON_CHANGE
			3- FALLING_EDGE
			4- RISING_EDGE
*/
#define EXT_INT1_SENSE       FALLING_EDGE

/************************************************************************/
/*         EXT_INT2_SENSE                                                                  */
/************************************************************************/
/*
  Options:   
            1- FALLING_EDGE
			2- RISING_EDGE
*/
#define EXT_INT2_SENSE       FALLING_EDGE

/************************************************************************/
/*         EXT_INT0_STATE                                                                  */
/************************************************************************/
/*
  Options:   
            1- ENABLED
			2- DISABLED
*/
#define EXT_INT0_STATE       ENABLED

/************************************************************************/
/*         EXT_INT1_STATE                                                                  */
/************************************************************************/
/*
  Options:   
            1- ENABLED
			2- DISABLED
*/
#define EXT_INT1_STATE       ENABLED

/************************************************************************/
/*         EXT_INT2_STATE                                                                  */
/************************************************************************/
/*
  Options:   
            1- ENABLED
			2- DISABLED
*/
#define EXT_INT2_STATE       ENABLED


#endif /* EXT_INTERRUPT_CONFIGURATION_H_ */