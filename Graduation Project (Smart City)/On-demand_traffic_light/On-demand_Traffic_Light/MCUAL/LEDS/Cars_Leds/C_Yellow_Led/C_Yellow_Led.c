/*
 * C_Yellow_Led.c
 *
 * Created: 13/12/2022 08:42:09 م
 *  Author: Apple
 */ 
#include "C_Yellow_Led.h"

void C_Yellow_Led_Initialize(void)
{
	DIO_SETPIN_DIRECTION(C_Yellow_Led_PRT,C_Yellow_Led , DIO_OUTPUT);
}
void C_Yellow_Led_ON(void)
{
	DIO_SETPIN_VALUE(C_Yellow_Led_PRT,C_Yellow_Led,DIO_HIGH);
}
void C_Yellow_Led_OFF(void)
{
	DIO_SETPIN_VALUE(C_Yellow_Led_PRT,C_Yellow_Led,DIO_LOW);
	
}
void C_Yellow_Led_TGL(void)
{
	DIO_TOGPIN_VALUE(C_Yellow_Led_PRT,C_Yellow_Led);
}