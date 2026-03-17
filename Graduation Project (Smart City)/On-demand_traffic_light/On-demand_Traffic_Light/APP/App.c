


#include "App.h"

uint8_t Mode ='A';//select between two modes : A->(car mode) B->(pedstrain mode)
uint8_t car_led_status=0;//determines the status of car leds
void APP_inititialize(void)
{

	
	C_Green_Led_Initialize();
	C_Red_Led_Initialize();
	C_Yellow_Led_Initialize();
	
	
	P_Green_Led_Initialize();
	P_Red_Led_Initialize();
	P_Yellow_Led_Initialize();
	
	
	Button_Initialization();
	
	
	TIMER_initialize();
	
	
	sei();
	RISING_EDGE_SETUP();
	SETUP_INT0();
} 


void APP_start(void)
{
	int i=0;
	
	switch(car_led_status)
	{
		case 0: // car green led 
		    if (Mode=='A') //normal mode
		    {
				//tern off the pedestrian led s
				P_Yellow_Led_OFF();
				P_Green_Led_OFF();
				P_Red_Led_OFF();
				//tern on cars green led
				C_Green_Led_ON();
				C_Yellow_Led_OFF();
				C_Red_Led_OFF();
				
				for(i=0;i<100;i++)
				{
					TIMER_delay(50);
					if(!Mode)
					break;
				}
				car_led_status=1;
				
		    }
			else if (Mode=='B')//ped mode
			{
				 C_Green_Led_ON();
				 C_Yellow_Led_OFF();
				 C_Red_Led_OFF();
				 
				 P_Green_Led_OFF();
				 P_Yellow_Led_OFF();
				 P_Red_Led_ON();
				 
				 
				 for(i=0;i<100;i++)
				 {
					 TIMER_delay(50);
					 
				 }
				 car_led_status=1;
			}
			break;
			
	     case 1://cars yellow led
		 if (Mode=='A') //normal mode
		 {
			for(i=0;i<20;i++)
			{
				
				C_Yellow_Led_ON();
				TIMER_delay(100);
				C_Yellow_Led_OFF();
				TIMER_delay(50);
				C_Yellow_Led_ON();
				TIMER_delay(100);
				if(!Mode)
				break;
			}
			 car_led_status=2;
			 
		 }
		 else if (Mode=='B')//ped mode
		 {
			 for(i=0;i<20;i++)
			 {
				 
				 C_Yellow_Led_ON();
				 P_Yellow_Led_ON();
				 TIMER_delay(100);
				 C_Yellow_Led_OFF();
				 P_Yellow_Led_OFF();
				 TIMER_delay(50);
				 C_Yellow_Led_ON();
				 P_Yellow_Led_ON();
				 TIMER_delay(100);
				 
			 }
			 car_led_status=2;
		 }
		 break;
		 
		  case 2://cars red led
		  if (Mode=='A') //normal mode
		  {
			C_Green_Led_OFF();
			C_Yellow_Led_OFF();
			C_Red_Led_ON();
			
			for(i=0;i<100;i++)
			{
				TIMER_delay(50);
				if(!Mode)
				break;
			}
			for(i=0;i<20;i++)
			{
				
				C_Yellow_Led_ON();
				TIMER_delay(100);
				C_Yellow_Led_OFF();
				TIMER_delay(50);
				C_Yellow_Led_ON();
				TIMER_delay(100);
				if(!Mode)
				break;
			}
			 car_led_status=0;
			  
			  
		  }
		  else if (Mode=='B')//ped mode
		  {
			C_Green_Led_OFF();
			C_Yellow_Led_OFF();
			C_Red_Led_ON();
			
			P_Green_Led_ON();
			P_Yellow_Led_OFF();
			P_Red_Led_OFF();
			
			for(i=0;i<100;i++)
			{
				TIMER_delay(50);
				
			}
			for(i=0;i<20;i++)
			{
				
				C_Yellow_Led_ON();
				P_Yellow_Led_ON();
				TIMER_delay(100);
				C_Yellow_Led_OFF();
				P_Yellow_Led_OFF();
				TIMER_delay(50);
				C_Yellow_Led_ON();
				P_Yellow_Led_ON();
				TIMER_delay(100);
				
			}
			Mode='A';
			  car_led_status=0;
		  }
		  break;
		  
	
		
	}
	
}

ISR(EXT_INT_0){
	Mode='B';
}