/*
 * P_Green_Led.c
 *
 * Created: 13/12/2022 08:45:01 م
 *  Author: Apple
 */ 
#include "P_Green_Led.h"

void P_Green_Led_Initialize(void)
{
	DIO_SETPIN_DIRECTION(P_Green_Led_PRT,P_Green_Led , DIO_OUTPUT);
}
void P_Green_Led_ON(void)
{
	DIO_SETPIN_VALUE(P_Green_Led_PRT,P_Green_Led,DIO_HIGH);
}
void P_Green_Led_OFF(void)
{
	DIO_SETPIN_VALUE(P_Green_Led_PRT,P_Green_Led,DIO_LOW);
	
}
void P_Green_Led_TGL(void)
{
	DIO_TOGPIN_VALUE(P_Green_Led_PRT,P_Green_Led);
}