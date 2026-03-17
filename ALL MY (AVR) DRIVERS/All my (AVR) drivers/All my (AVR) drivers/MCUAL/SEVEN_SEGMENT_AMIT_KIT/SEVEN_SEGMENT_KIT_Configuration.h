/*
 * SEVEN_SEGMENT_KIT_Configuration.h
 *
 * Created: 25/11/2023 02:33:35 م
 *  Author: Moustafa El-hanash
 */ 


#ifndef SEVEN_SEGMENT_KIT_CONFIGURATION_H_
#define SEVEN_SEGMENT_KIT_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

#define SEVEN_SEGMENT_CENTRAL_PORT      GPIO_PORTB
#define SEVEN_SEGMENT_DATA_PORT         GPIO_PORTA
/************************************************************************/
/* Central Pins                                                                     */
/************************************************************************/
#define EN1_PIN                             GPIO_PIN1
#define EN2_PIN                             GPIO_PIN2
#define DIP_PIN                             GPIO_PIN3
/************************************************************************/
/* Data Pins                                                                     */
/************************************************************************/
#define DATA_A_PIN                          GPIO_PIN4
#define DATA_B_PIN                          GPIO_PIN5
#define DATA_C_PIN                          GPIO_PIN6
#define DATA_D_PIN                          GPIO_PIN7



#endif /* SEVEN_SEGMENT_KIT_CONFIGURATION_H_ */