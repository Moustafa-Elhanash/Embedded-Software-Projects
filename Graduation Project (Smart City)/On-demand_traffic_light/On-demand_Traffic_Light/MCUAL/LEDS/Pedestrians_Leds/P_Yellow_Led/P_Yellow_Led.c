/*
 * P_Yellow_Led.c
 *
 * Created: 13/12/2022 08:43:38 م
 *  Author: Apple
 */ 
#include "P_Yellow_Led.h"

void P_Yellow_Led_Initialize(void)
{
	DIO_SETPIN_DIRECTION(P_Yellow_Led_PRT,P_Yellow_Led , DIO_OUTPUT);
}
void P_Yellow_Led_ON(void)
{
	DIO_SETPIN_VALUE(P_Yellow_Led_PRT,P_Yellow_Led,DIO_HIGH);
}
void P_Yellow_Led_OFF(void)
{
	DIO_SETPIN_VALUE(P_Yellow_Led_PRT,P_Yellow_Led,DIO_LOW);
	
}
void P_Yellow_Led_TGL(void)
{
	DIO_TOGPIN_VALUE(P_Yellow_Led_PRT,P_Yellow_Led);
}