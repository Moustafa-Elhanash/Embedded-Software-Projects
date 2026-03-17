/*
 * All my (AVR) drivers.c
 *
 * Created: 19/11/2023 04:17:04 
 * Author : Moustafa El-hanash
 */ 

#include "App.h"
#include "Traffic.h"

int main(void)
{

//APP_INIT();
TRAFFIC_INIT();
    while (1) 
    {
	
	
	
 //APP_START();
 TRAFFIC_START();
	}
}
void ADC_NOTIFICATION(void)
{
	
	/* nothing */
}