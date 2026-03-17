/*
 * ULTRASONIC_Program.c
 *
 * Created: 20/02/2024 03:31:12 م
 *  Author:moustafa
 */ 

#include "ULTRASONIC_Private.h"
uint16 a,b,high,distance;


void ULTRASONIC_INIT(const ULTRASONIC_CONFIG_t *ultrasonic)
{
GPIO_SETPIN_DIRECTION(ultrasonic->ultrasonic_Port,ultrasonic->ultrasonic_trig_Pin,GPIO_OUTPUT);

}
uint16 ULTRASONIC_START_MEASURE(const ULTRASONIC_CONFIG_t *ultrasonic)
{
 TCCR1A = 0;
 // Clear Input Capture flag
 SET_BIT(TIFR,5);
 // Generate pulse to enable ultrasonic sensor
 GPIO_SETPIN_VALUE(ultrasonic->ultrasonic_Port,ultrasonic->ultrasonic_trig_Pin,GPIO_HIGH);
 _delay_us(20);
 GPIO_SETPIN_VALUE(ultrasonic->ultrasonic_Port,ultrasonic->ultrasonic_trig_Pin,GPIO_LOW);
 // Configure Timer1 for rising edge detection, no prescaler
 TCCR1B = 0xc1;
  while ((TIFR&(1<<5)) == 0);
  a = ICR1;  		/* Take value of capture register */
  TIFR = (1<<5);  	/* Clear ICF flag */
  TCCR1B = 0x81;  	/* Falling edge, no prescaler ,noise canceler*/
  while ((TIFR&(1<<5)) == 0);
  b = ICR1;  		/* Take value of capture register */
  TIFR = (1<<5);  	/* Clear ICF flag */
  TCNT1=0;
  TCCR1B = 0;  		/* Stop the timer */
  high=b-a;
  distance=((high*34600)/(F_CPU*2)) ;
 return distance;
}

