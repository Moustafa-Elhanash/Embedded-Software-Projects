/*
 * BUZZER_Program.c
 *
 * Created: 25/11/2023 04:18:51 م
 *  Author: MOUSTAFA
 */ 


#include "BUZZER_Private.h"


void BUZZER_INIT(const BUZZER_CONFIG_t *buzzer)
{
	GPIO_SETPIN_DIRECTION(buzzer->BuzzerPort,buzzer->BuzzerPin,GPIO_OUTPUT);
}
void BUZZER_ON(const BUZZER_CONFIG_t *buzzer)
{
	GPIO_SETPIN_VALUE(buzzer->BuzzerPort,buzzer->BuzzerPin,GPIO_HIGH);
}
void BUZZER_OFF(const BUZZER_CONFIG_t *buzzer)
{
	GPIO_SETPIN_VALUE(buzzer->BuzzerPort,buzzer->BuzzerPin,GPIO_LOW);
}