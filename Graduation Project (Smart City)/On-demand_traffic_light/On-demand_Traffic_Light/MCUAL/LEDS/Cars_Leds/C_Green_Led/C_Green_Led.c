/*
 * C_Green_Led.c
 *
 * Created: 13/12/2022 08:39:09 م
 *  Author: Apple
 */ 
#include "C_Green_Led.h"

void C_Green_Led_Initialize(void)
{
	DIO_SETPIN_DIRECTION(C_Green_Led_PRT,C_Green_Led , DIO_OUTPUT);
}
void C_Green_Led_ON(void)
{
	DIO_SETPIN_VALUE(C_Green_Led_PRT,C_Green_Led,DIO_HIGH);
}
void C_Green_Led_OFF(void)
{
	DIO_SETPIN_VALUE(C_Green_Led_PRT,C_Green_Led,DIO_LOW);
	
}
void C_Green_Led_TGL(void)
{
	DIO_TOGPIN_VALUE(C_Green_Led_PRT,C_Green_Led);
}