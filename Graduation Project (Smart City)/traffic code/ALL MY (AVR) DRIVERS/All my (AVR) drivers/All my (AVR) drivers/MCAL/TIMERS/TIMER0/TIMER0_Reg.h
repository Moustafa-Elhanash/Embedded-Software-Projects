/*
 * TIMER0_Reg.h
 *
 * Created: 15/02/2024 10:20:16 م
 *  Author: moustafa
 */ 


#ifndef TIMER0_REG_H_
#define TIMER0_REG_H_


#define  TCCR0       (*(volatile uint8*)(0X53))   /*Timer/Counter 0 control register */
#define  TCCR0_FOC0   7
#define  TCCR0_WGM00  6                           /*waveform generation mode bit 0*/
#define  TCCR0_COM01  5
#define  TCCR0_COM00  4
#define  TCCR0_WGM01  3                           /*waveform generation mode bit 1*/

#define  TCNT0       (*(volatile uint8*)(0X52))   /*Timer/Counter 0 register */

#define  OCR0        (*(volatile uint8*)(0X5C))   /*Timer/Counter 0 Output compare register */

#define  TIMSK       (*(volatile uint8*)(0X59))   /*Timer mask Register */
#define  TIMSK_TOIE0   0                          /*Timer0 overflow interrupt enable*/
#define  TIMSK_OCIE0   1                          /*Timer0 output compare interrupt enable*/

#define  TIFR        (*(volatile uint8*)(0X58))   /*Timer/Counter 0 interrupt flag register */
#define  TIFR_TOV0     0                          /*output compare flag*/
#define  TIFR_OCF0     1                          /*overflow flag*/



#endif /* TIMER0_REG_H_ */