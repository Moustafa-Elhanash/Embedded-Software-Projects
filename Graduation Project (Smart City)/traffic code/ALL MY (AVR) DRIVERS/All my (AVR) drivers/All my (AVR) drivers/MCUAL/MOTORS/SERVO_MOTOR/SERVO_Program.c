/*
 * SERVO_Program.c
 *
 * Created: 01/02/2024 06:45:52 م
 *  Author: Moustafa El-Hanash
 */ 
#include "SERVO_Private.h"

void SERVO_INIT(const SERVO_CONFIG_t *servo)
{ 
	GPIO_SETPIN_DIRECTION(servo->servoPort,servo->servoPin,GPIO_OUTPUT);
}



