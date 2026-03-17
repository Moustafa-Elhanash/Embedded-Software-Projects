/*
 * IR_Program.c
 *
 * Created: 20/03/2024 05:26:43 م
 *  Author: win10
 */ 

#include "IR_Private.h"


void IR_INIT(IR_CONFIG_t *IR)
{
	/* set the direction of ir sensor pin as an input pin */
	GPIO_SETPIN_DIRECTION(IR->ir_port,IR->ir_pin,GPIO_INPUT);
}

uint8 IR_STATUS(IR_CONFIG_t *IR)
{
	uint8 ir_status = 0;
	ir_status = GPIO_READPIN_VALUE(IR->ir_port,IR->ir_pin);
	return ir_status;

}