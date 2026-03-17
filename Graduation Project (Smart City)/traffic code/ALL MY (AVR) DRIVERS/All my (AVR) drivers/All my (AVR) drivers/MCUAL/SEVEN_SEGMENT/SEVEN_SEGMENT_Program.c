/*
 * SEVEN_SEGMENT_Program.c
 *
 * Created: 23/11/2023 09:01:40 م
 *  Author: moustafa elhanash 
   breif  : this driver only for common cathod
 */ 
#include "SEVEN_SEGMENT_Private.h"


void SEVEN_SEGMENT_INIT(GPIO_PORT_t port)
{
	GPIO_SETPORT_DIRECTION(port,GPIO_OUTPUT);
}
void SEVEN_SEGMENT_DISPLAY_NUMBER(GPIO_PORT_t port,uint8 Number)
{
	uint8 seven_segment_data[] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
	GPIO_WRITE_ON_PORT(port,seven_segment_data[Number]);
}
void SEVEN_SEGMENT_DISPLAY_CHAR(GPIO_PORT_t port,uint8 Letter)
{
	GPIO_WRITE_ON_PORT(port,Letter);
}
void SEVEN_SEGMENT_STOP(GPIO_PORT_t port)
{
	GPIO_SETPORT_VALUE(port,GPIO_LOW);
}
