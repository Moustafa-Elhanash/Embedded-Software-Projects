/*
 * RELAY_Program.c
 *
 * Created: 25/11/2023 06:08:47 م
 *  Author: Moustafa
 */ 


#include "RELAY_Private.h"

void RELAY_INIT(const RELAY_CONFIG_t *relay)
{
	GPIO_SETPIN_DIRECTION(relay->RelayPort,relay->RelayPin,GPIO_OUTPUT);
}
void RELAY_ON(const RELAY_CONFIG_t *relay)
{
	GPIO_SETPIN_VALUE(relay->RelayPort,relay->RelayPin,GPIO_HIGH);
}
void RELAY_OFF(const RELAY_CONFIG_t *relay)
{
	GPIO_SETPIN_VALUE(relay->RelayPort,relay->RelayPin,GPIO_LOW);
}