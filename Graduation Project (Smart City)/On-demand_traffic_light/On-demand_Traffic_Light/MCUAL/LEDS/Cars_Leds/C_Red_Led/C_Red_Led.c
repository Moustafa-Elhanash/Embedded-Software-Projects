/*
 * C_Red_Led.c
 *
 * Created: 13/12/2022 08:41:14 م
 *  Author: Apple
 */ 

#include "C_Red_Led.h"

void C_Red_Led_Initialize(void)
{
	DIO_SETPIN_DIRECTION(C_Red_Led_PRT,C_Red_Led , DIO_OUTPUT);
}
void C_Red_Led_ON(void)
{
	DIO_SETPIN_VALUE(C_Red_Led_PRT,C_Red_Led,DIO_HIGH);
}
void C_Red_Led_OFF(void)
{
	DIO_SETPIN_VALUE(C_Red_Led_PRT,C_Red_Led,DIO_LOW);
	
}
void C_Red_Led_TGL(void)
{
	DIO_TOGPIN_VALUE(C_Red_Led_PRT,C_Red_Led);
}