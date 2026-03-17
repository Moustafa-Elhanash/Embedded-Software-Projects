/*
 * App.c
 *
 * Created: 21/11/2023 09:00:36 م
 *  Author: moustafa elhanash
 */ 

#include "App.h"

	/************************************************************************/
	/*     LEDS INTIALIZATION                                                                 */
	/************************************************************************/

/*

// LED0
 LED_CONFIG_t LED0={GPIO_PORTB,GPIO_PIN0,SOURCE_CONNECTION} ;

// LED1
LED_CONFIG_t LED1={GPIO_PORTB,GPIO_PIN1,SOURCE_CONNECTION} ;

// LED2
LED_CONFIG_t LED2={GPIO_PORTB,GPIO_PIN2,SOURCE_CONNECTION} ;
// LED3
LED_CONFIG_t LED3={GPIO_PORTB,GPIO_PIN3,SOURCE_CONNECTION} ;
// LED4
LED_CONFIG_t LED4={GPIO_PORTB,GPIO_PIN4,SOURCE_CONNECTION} ;
// LED5
LED_CONFIG_t LED5={GPIO_PORTB,GPIO_PIN5,SOURCE_CONNECTION} ;
// LED6
LED_CONFIG_t LED6={GPIO_PORTB,GPIO_PIN6,SOURCE_CONNECTION} ;
// LED7
LED_CONFIG_t LED7={GPIO_PORTB,GPIO_PIN7,SOURCE_CONNECTION} ;
*/
  /* ADC TEST
   uint16 adc_reading_1;
    float32 Analog_volt_1;
    float32 Temprature;
    uint16 adc_readings[8]={0};

	float32 Analog_volts[8]={0};

	float32 Tempratures[8]={0};
	//uint8   ADC_Completed_Results=0;
	uint8 counter1=0;*/
   
	/************************************************************************/
	/*      BUTTONS INTIALIZATION                                                                */
	/************************************************************************/

/*
// BUTTON0
BUTTON_CONFIG_t BUTTON0={BUTTON0_PRT,BUTTON0_PIN,PULL_DOWN};

// BUTTON1
BUTTON_CONFIG_t BUTTON1={BUTTON1_PRT,BUTTON1_PIN,PULL_DOWN};

// BUTTON2
BUTTON_CONFIG_t BUTTON2={BUTTON2_PRT,BUTTON2_PIN,PULL_DOWN};
	
	
*/

/*
     3- 7segment kit 
uint8 counter1=0,counter2=0,counter3=0;*/
/************************************************************************/
/*     BUZZER INTIALIZATION                                                                */
/************************************************************************/
/*
BUZZER_CONFIG_t Buzzer0={BUZZER0_PORT,BUZZER0_PIN};
*/
/************************************************************************/
/*    RELAY INTIALIZATION                                                                */
/************************************************************************/
/*
RELAY_CONFIG_t relay0={RELAY0_PORT,RELAY0_PIN};
	*/
/************************************************************************/
/*  STEPPER MOTOR INTIALIZATION                                                                */
/************************************************************************/
/*
STEPPER_CONFIG_t Stepper_motor={STEPPER_PORT,STEPPER_COIL_A_PLUS,STEPPER_COIL_A_MINUS,STEPPER_COIL_B_PLUS,STEPPER_COIL_B_MINUS,Half_step,Step_CCW};
*/
/*
 / *3- 7segment kit * /
uint8 counter1=0;
uint8 counter2=0;
uint8 counter3=0;*/


 
void APP_INIT(void)
{
	
	
	/*
	ADC
	
	GPIO_SETPORT_DIRECTION(GPIO_PORTA,GPIO_INPUT);

	ADC_INIT();
	LCD_INIT();
	EXT_ENABLE_GLOBAL();*/
	
	
	
/*
	BUTTON_INIT(&BUTTON0);
	BUTTON_INIT(&BUTTON1);
	BUTTON_INIT(&BUTTON2);*/
	
	/*
	ext_interrupt
	
	LED_INIT(&LED0);
	LED_INIT(&LED1);
	LED_INIT(&LED2);
    SEVEN_SEGMENT_INIT(GPIO_PORTA);
	EXT_INTERRUPT_INIT();
	
	EXT_ENABLE_GLOBAL();
	 void ISR0(void)
	{
		LED_TGL(&LED0);
	}
	void ISR2(void)
	{
		SEVEN_SEGMENT_STOP(GPIO_PORTA);
		if (counter1)
		{
			counter1--;
		}
		else
		{
			/ *nothing * /
		}
		
	}
	void ISR1(void)
	{
		SEVEN_SEGMENT_STOP(GPIO_PORTA);
		counter1++;
	}
	
	EXT_SET_CALL_BACK(INT0,&ISR0);
	EXT_SET_CALL_BACK(INT1,&ISR1);
	EXT_SET_CALL_BACK(INT2,&ISR2);*/
/*
	 / *3- 7segment kit * /
	SEVEN_SEGMENT_KIT_INIT();*/

/*	

STEPPER_INIT(&Stepper_motor);*/
}
void APP_START(void)
{
/*  ADC ASyn chain
ADC_START_CHAIN_CONVERSION_ASYN(ADC_SINGLE_ENDED_CH0,adc_readings,&ADC_NOTIFICATION);

for (counter1 = ADC_SINGLE_ENDED_CH0;counter1<8;counter1++)
{
	Analog_volts[counter1]=(((uint32)(adc_readings[counter1]))*5000UL)/1024;
	Tempratures[counter1] = (Analog_volts[counter1])/10;
	
}
 LCD_SET_CURSOR(0,0);
 LCD_WRITE_FLOAT(Tempratures[0]);
 LCD_SET_CURSOR(0,6);
 LCD_WRITE_STRING("-");
 LCD_SET_CURSOR(0,7);
 LCD_WRITE_FLOAT(Tempratures[1]);
 LCD_SET_CURSOR(1,0);
 LCD_WRITE_FLOAT(Tempratures[2]);
 LCD_SET_CURSOR(1,6);
 LCD_WRITE_STRING("-");
 LCD_SET_CURSOR(1,7);
 LCD_WRITE_FLOAT(Tempratures[3]); 

 LCD_CLEAR_SCREEN();*/
/* ADC ASyn
	ADC_START_CONVERSION_ASYN(ADC_SINGLE_ENDED_CH0,&adc_reading_1,&ADC_NOTIFICATION);
	  Analog_volt_1 =((((uint32)adc_reading_1)*5000UL)/1024);  // 1024 for ten bit
	Temprature = Analog_volt_1/10;
	
	 LCD_SET_CURSOR(0,0);
	 LCD_WRITE_STRING("Temp =");
	 LCD_SET_CURSOR(0,6);
	 LCD_WRITE_FLOAT(Temprature);
	*/
	 
	/* ADC SYNC 
	 ADC_START_CONVERSION_SYN(ADC_SINGLE_ENDED_CH1, &adc_reading_1);
	 
	  Analog_volt_1 =((((uint32)adc_reading_1)*5000UL)/1024);  // 1024 for ten bit
	  Temprature=Analog_volt_1/10;
	  
	
	  LCD_SET_CURSOR(0,0);
	  LCD_WRITE_STRING("Temp =");
	  LCD_SET_CURSOR(0,6);
	  LCD_WRITE_FLOAT(Temprature);
	
	  LCD_CLEAR_SCREEN();
	*/
	
/* ADC syn chain 
    ADC_START_CONVERSION_SYN(ADC_SINGLE_ENDED_CH1, &adc_reading_1);
  / *  - lm35 sensor * /
   Analog_volt_1 =((((uint32)adc_reading_1)*5000UL)/256);
   Temprature=Analog_volt_1/10;
   ADC_START_CONVERSION_SYN(ADC_SINGLE_ENDED_CH0,&adc_reading_0);
   Analog_volt_0 =((adc_reading_0*5)/256);
   LCD_SET_CURSOR(0,0);
   LCD_WRITE_STRING("Temp =");
   LCD_SET_CURSOR(0,6);
   LCD_WRITE_NUMBER(Temprature);
   LCD_SET_CURSOR(1,0);
   LCD_WRITE_NUMBER(Analog_volt_0);
   _delay_ms(100);
   LCD_CLEAR_SCREEN();*/
/*
	ext_interrupt
	if (counter1 <= 9)
	{
		SEVEN_SEGMENT_DISPLAY_NUMBER(GPIO_PORTA,counter1);
	} 
	else
	{
		counter1 = 0;
	}*/
	
/*
	STEPPER_ROTATE(&Stepper_motor);

	*/
		
	/*BUZZER_ON(&Buzzer0);
	_delay_ms(300);
	BUZZER_OFF(&Buzzer0);
	_delay_ms(150);
	BUZZER_ON(&Buzzer0);
	_delay_ms(100);
	BUZZER_OFF(&Buzzer0);
	_delay_ms(40);
	BUZZER_ON(&Buzzer0);
	_delay_ms(100);
	BUZZER_OFF(&Buzzer0);
	_delay_ms(40);
	BUZZER_ON(&Buzzer0);
	_delay_ms(100);
	BUZZER_OFF(&Buzzer0);
	_delay_ms(40);
	
 _delay_ms(3000);*/	
	/*
	   1- leds With buttons
	if (1 == BUTTON_READ(&BUTTON0,&error_state))
	{
		LED_TGL(&LED0);
	}
	_delay_ms(25);
	if (1 == BUTTON_READ(&BUTTON1,&error_state))
	{
		LED_TGL(&LED1);
	}	
	_delay_ms(25);	
	if (1 == BUTTON_READ(&BUTTON2,&error_state))
	{
		LED_TGL(&LED2);
	}
	_delay_ms(25);*/
	/*
	
	  2- 7segment normal
	
	
	SEVEN_SEGMENT_DISPLAY_CHAR(SEVEN_SEGMENT_PORT,A);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_CHAR(SEVEN_SEGMENT_PORT,B);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_CHAR(SEVEN_SEGMENT_PORT,C);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_CHAR(SEVEN_SEGMENT_PORT,E);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_CHAR(SEVEN_SEGMENT_PORT,F);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_CHAR(SEVEN_SEGMENT_PORT,G);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_CHAR(SEVEN_SEGMENT_PORT,H);	
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,0);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,1);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,2);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,3);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,4);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,5);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,6);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,7);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,8);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);
	SEVEN_SEGMENT_DISPLAY_NUMBER(SEVEN_SEGMENT_PORT,9);
	_delay_ms(1000);
	SEVEN_SEGMENT_STOP(SEVEN_SEGMENT_PORT);*/
/*
	  / *3- 7segment kit * /
	
	SEVEN_SEGMENT_KIT_EN1_ONLY();
	SEVEN_SEGMENT_KIT_DISPLAY(5);
	_delay_ms(1000);
	SEVEN_SEGMENT_KIT_EN2_ONLY();
	SEVEN_SEGMENT_KIT_DISPLAY(5);
	_delay_ms(1000);
	for (counter1=0;counter1<=9;counter1++)
	{
		for (counter2=0;counter2<=9;counter2++)
		{
			for (counter3=0;counter3<60;counter3++)
			{
				SEVEN_SEGMENT_KIT_EN1_ONLY();
				SEVEN_SEGMENT_KIT_DISPLAY(counter2);
				_delay_ms(5);
				SEVEN_SEGMENT_KIT_EN2_ONLY();
				SEVEN_SEGMENT_KIT_DISPLAY(counter1);
				_delay_ms(5);
			}
		}
	}
	
		SEVEN_SEGMENT_KIT_DISABLE_ALL();
		counter1=0;
		counter2=0;
		counter3=0;*/
/*
	RELAY_ON(&relay0);
	_delay_ms(1000);
	RELAY_OFF(&relay0);
	_delay_ms(1000);*/
}
