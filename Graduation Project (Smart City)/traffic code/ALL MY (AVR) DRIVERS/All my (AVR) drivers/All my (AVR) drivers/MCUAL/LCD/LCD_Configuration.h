/*
 * LCD_Configuration.h
 *
 * Created: 26/11/2023 07:29:29 م
 *  Author: Moustafa
 */ 


#ifndef LCD_CONFIGURATION_H_
#define LCD_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

#define EIGHT_BIT_MODE    1
#define FOUR_BIT_MODE     2

/************************************************************************/
/*   CHOOSE MODE  :
     
	                  1- EIGHT_BIT_MODE
					  2- FOUR_BIT_MODE
                                                                       */
/************************************************************************/

#define LCD_MODE    FOUR_BIT_MODE   // choose


#if (LCD_MODE ==  EIGHT_BIT_MODE)
   /************************************************************************/
   /* 8Bit Mode                                                                     */
   /************************************************************************/
   #define LCD_DATA_PORT     GPIO_PORTA
   #define LCD_CONTROL_PORT  GPIO_PORTB
   // Control pins
   #define LCD_RS_PIN         GPIO_PIN1
   #define LCD_RW_PIN         GPIO_PIN2
   #define LCD_EN_PIN         GPIO_PIN3
   // Data pins
   #define LCD_D0_PIN         GPIO_PIN0
   #define LCD_D1_PIN         GPIO_PIN1
   #define LCD_D2_PIN         GPIO_PIN2
   #define LCD_D3_PIN         GPIO_PIN3
   #define LCD_D4_PIN         GPIO_PIN4
   #define LCD_D5_PIN         GPIO_PIN5
   #define LCD_D6_PIN         GPIO_PIN6
   #define LCD_D7_PIN         GPIO_PIN7

#elif (LCD_MODE ==  FOUR_BIT_MODE)

/************************************************************************/
/* 4Bit Mode                                                                 */
/************************************************************************/
   #define LCD_DATA_PORT     GPIO_PORTC
   #define LCD_CONTROL_PORT  GPIO_PORTC
   // Control pins
   #define LCD_RS_PIN         GPIO_PIN1
   #define LCD_RW_PIN         GPIO_PIN2
   #define LCD_EN_PIN         GPIO_PIN3
   // Data pins
   #define LCD_D4_PIN         GPIO_PIN4
   #define LCD_D5_PIN         GPIO_PIN5
   #define LCD_D6_PIN         GPIO_PIN6
   #define LCD_D7_PIN         GPIO_PIN7

#endif



#endif /* LCD_CONFIGURATION_H_ */