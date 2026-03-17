/*
 * On-demand_Traffic_Light.c
 *
 * Created: 13/12/2022 07:54:28 
 * Author : <Moustafa Elhanash>
 */ 
#include <avr/io.h>             // This header file includes the appropriate Input/output definitions for the device
#include <util/delay.h>         // to use delay function we need to include this library
#include <stdlib.h>             // we'll be using itoa() function to convert integer to character array that resides in this library

#include "App.h"


int main(void)
{
	
	
   APP_inititialize();
    while (1) 
    {
		APP_start(); 
		
		
    }
}

