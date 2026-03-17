/*
 * P_Red_Led.c
 *
 * Created: 13/12/2022 08:43:50 م
 *  Author: Apple
 */ 
#include "P_Red_Led.h"

void P_Red_Led_Initialize(void)
{
	DIO_SETPIN_DIRECTION(P_Red_Led_PRT,P_Red_Led , DIO_OUTPUT);
}
void P_Red_Led_ON(void)
{
	DIO_SETPIN_VALUE(P_Red_Led_PRT,P_Red_Led,DIO_HIGH);
}
void P_Red_Led_OFF(void)
{
	DIO_SETPIN_VALUE(P_Red_Led_PRT,P_Red_Led,DIO_LOW);
	
}
void P_Red_Led_TGL(void)
{
	DIO_TOGPIN_VALUE(P_Red_Led_PRT,P_Red_Led);
}