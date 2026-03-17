/*
 * Traffic.c
 *
 * Created: 15/02/2024 02:48:25 م
 *  Author: Moustafa 
 */ 

#include "Traffic.h"
/**************************************on demand traffic light*******************************************************************/
//select between two modes : A->(car mode) B->(pedstrain mode)
uint8 Mode ='A'; 
volatile uint16 CTC_counter = 0;
/************************************************************************/
/*     LEDS INTIALIZATION        */
/************************************************************************/ 
// LED_C_RED
LED_CONFIG_t LED_C_RED={GPIO_PORTA,GPIO_PIN2,SOURCE_CONNECTION} ;

// LED_C_YELLOW
LED_CONFIG_t LED_C_YELLOW={GPIO_PORTA,GPIO_PIN1,SOURCE_CONNECTION} ;

// LED_C_GREEN
LED_CONFIG_t LED_C_GREEN={GPIO_PORTA,GPIO_PIN0,SOURCE_CONNECTION} ;
// LED_P_RED
LED_CONFIG_t LED_P_RED={GPIO_PORTB,GPIO_PIN2,SOURCE_CONNECTION} ;
// LED_P_YELLOW
LED_CONFIG_t LED_P_YELLOW={GPIO_PORTB,GPIO_PIN1,SOURCE_CONNECTION} ;
// LED_P_GREEN
LED_CONFIG_t LED_P_GREEN={GPIO_PORTB,GPIO_PIN0,SOURCE_CONNECTION} ;
/***********************************************************************************************************************/
/**************************************smart parking *******************************************************************/
ULTRASONIC_CONFIG_t p1 = {GPIO_PORTB,GPIO_PIN3};
ULTRASONIC_CONFIG_t p2 = {GPIO_PORTB,GPIO_PIN4};
ULTRASONIC_CONFIG_t G_IN = {GPIO_PORTB,GPIO_PIN5};
ULTRASONIC_CONFIG_t G_OUT = {GPIO_PORTB,GPIO_PIN6};	
	
uint16 distance_p1 =0,distance_p2 = 0, distance_G_IN = 0,distance_G_OUT = 0;

volatile uint8 timer2_counter =0 ;
volatile uint8 servo_timeOn = 8 ;   // 8- servo 0 degree  12- servo 90 degree
uint8 p1_flag =0, p2_flag =0, complete_flag =0;
uint8 places = 0;


SERVO_CONFIG_t servo_in ={GPIO_PORTA,GPIO_PIN3};

/***********************************************************************************************************************/
void TRAFFIC_INIT(void)
{
	/**************************************smart parking *******************************************************************/
    ULTRASONIC_INIT(&p1);
	ULTRASONIC_INIT(&p2);
    ULTRASONIC_INIT(&G_IN);
    ULTRASONIC_INIT(&G_OUT);
	TIMER2_INIT();
	SERVO_INIT(&servo_in);  // for enter gate
	TIMER2_SET_CALL_BACK(CTC_INTERRUPT,&TIMER2_CTC_ISR);
	/***************************on demand traffic light***************************************************/
	LED_INIT(&LED_C_RED);
	LED_INIT(&LED_C_YELLOW);
	LED_INIT(&LED_C_GREEN);
	LED_INIT(&LED_P_RED);
	LED_INIT(&LED_P_YELLOW);
	LED_INIT(&LED_P_GREEN);
	LCD_INIT();
	TIMER0_INIT();
	EXT_INTERRUPT_INIT();
	EXT_ENABLE_GLOBAL();
	EXT_SET_CALL_BACK(INT0,&ISR0);
	TIMER0_SET_CALL_BACK(CTC_INTERRUPT,&TIMER0_CTC_ISR);
	/*******************************************************************************************************/
	
}

void TRAFFIC_START(void)
{
	/* parking App loop*/
	/* getting reading of sensors */
   distance_p1 = ULTRASONIC_START_MEASURE(&p1) ;
   distance_p2 = ULTRASONIC_START_MEASURE(&p2) ;
   distance_G_IN = ULTRASONIC_START_MEASURE(&G_IN);
   distance_G_OUT= ULTRASONIC_START_MEASURE(&G_OUT);
    /* place 1 check */
   if (distance_p1 < 10)
   {
	   p1_flag = 1; // the place is reserved
   } 
   else
   {
	   p1_flag = 0; // the place is empty
   }
   /* place 2 check */
   if (distance_p2 < 10)
   {
	   p2_flag = 1;  // the place is reserved
   } 
   else
   {
	   p2_flag = 0;  // the place is empty
   }
    /* overall check */
   if ((p1_flag == 1) && (p2_flag == 1))
   {
	   complete_flag = 1; // complete places
   } 
   else
   {
	   complete_flag = 0;  
   }
    places = p1_flag + p2_flag;   // if the place reserved his flag will = 1
   /* enter gate */
   if (((distance_G_IN < 10) && (complete_flag == 0)) || (distance_G_OUT < 10))
   {
	    /* servo (gate) on */
		servo_timeOn = 12;
		  /* print parking data on lcd */
		
		  LCD_SET_CURSOR(0,0);
		  LCD_WRITE_STRING("Available places");
		  LCD_SET_CURSOR(1,7);
		  LCD_WRITE_NUMBER((2-places));
		
   } 
   else if ((distance_G_IN < 10) && (complete_flag == 1))
   {
	   /* servo (gate) off */
	   servo_timeOn = 8;
	   LCD_SET_CURSOR(0,0);
	   LCD_WRITE_STRING("Parking Complete");
	   LCD_SET_CURSOR(1,0);
	   LCD_WRITE_STRING("                ");
   }
   else
   {
	   /* servo (gate) off */
	   servo_timeOn = 8;
	   /* print parking data on lcd */
	   
	   LCD_SET_CURSOR(0,0);
	   LCD_WRITE_STRING("Available places");
	   LCD_SET_CURSOR(1,7);
	   LCD_WRITE_NUMBER((2-places)); 
   }
 
}

void TIMER0_CTC_ISR(void)
{
	//static uint8 counter = 0 ;
	CTC_counter++;
	// for each second we need 250 ctc
	if (CTC_counter < 1250)
	{
		if (Mode == 'A') // normal mode
		{
			//turn off the pedestrian led s
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led
			LED_OFF(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
		}
		else if (Mode == 'B') //pedestrian mode
		{
			//turn on cars green led
			LED_OFF(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
			//turn on the pedestrian red led 
			LED_ON(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			
			
		}
		
	}
	else if (CTC_counter == 1250)
	{
		if (Mode == 'A') // normal mode
		{
			//turn off the pedestrian led s
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_OFF(&LED_C_RED);
			LED_ON(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
		}
		else if (Mode == 'B') //pedestrian mode
		{
		
			LED_ON(&LED_P_RED);
			LED_ON(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_OFF(&LED_C_RED);
			LED_ON(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
			
		}
	}
	else if (CTC_counter == 1500)
	{
		if (Mode == 'A') // normal mode
		{
			//turn off the pedestrian led s
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led
			LED_OFF(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
		}
		else if (Mode == 'B') //pedestrian mode
		{
			
			LED_ON(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led
			LED_OFF(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
			
		}
	}
	else if (CTC_counter == 1750)
	{
		if (Mode == 'A') // normal mode
		{
			//turn off the pedestrian led s
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_OFF(&LED_C_RED);
			LED_ON(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
		}
		else if (Mode == 'B') //pedestrian mode
		{
			
			LED_ON(&LED_P_RED);
			LED_ON(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_OFF(&LED_C_RED);
			LED_ON(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
			
		}
	}
	else if (CTC_counter == 2000)
	{
		if (Mode == 'A') // normal mode
		{
			//turn off the pedestrian led s
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led
			LED_OFF(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
		}
		else if (Mode == 'B') //pedestrian mode
		{
			
			LED_ON(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led
			LED_OFF(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
			
		}
	}
	else if (CTC_counter == 2250)
	{
		if (Mode == 'A') // normal mode
		{
			//turn off the pedestrian led s
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_OFF(&LED_C_RED);
			LED_ON(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
		}
		else if (Mode == 'B') //pedestrian mode
		{
			
			LED_ON(&LED_P_RED);
			LED_ON(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_OFF(&LED_C_RED);
			LED_ON(&LED_C_YELLOW);
			LED_ON(&LED_C_GREEN);
			
		}
	}
	else if (CTC_counter == 2500)
	{
		if (Mode == 'A') // normal mode
		{
			//turn off the pedestrian led s
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_OFF(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_ON(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_OFF(&LED_C_GREEN);
		}
		else if (Mode == 'B') //pedestrian mode
		{
		
			LED_OFF(&LED_P_RED);
			LED_OFF(&LED_P_YELLOW);
			LED_ON(&LED_P_GREEN);
			//turn on cars green led & yellow
			LED_ON(&LED_C_RED);
			LED_OFF(&LED_C_YELLOW);
			LED_OFF(&LED_C_GREEN);
			
			
		}
	}
	else if (CTC_counter == 3750)
	{
		CTC_counter = 0;
		Mode = 'A';
	}
	
	
}
void ISR0(void)
{
	Mode = 'B';
	
}
void TIMER2_CTC_ISR(void)
{
	timer2_counter ++;
	/* for 90 degree */
	if (timer2_counter >= servo_timeOn)
	{
		GPIO_SETPIN_VALUE(servo_in.servoPort,servo_in.servoPin,GPIO_LOW);
	} 
	else if (timer2_counter >= 160)
	{
		GPIO_SETPIN_VALUE(servo_in.servoPort,servo_in.servoPin,GPIO_HIGH);
		timer2_counter = 0;
	}
	else
	{
		GPIO_SETPIN_VALUE(servo_in.servoPort,servo_in.servoPin,GPIO_HIGH);
	}
	
}