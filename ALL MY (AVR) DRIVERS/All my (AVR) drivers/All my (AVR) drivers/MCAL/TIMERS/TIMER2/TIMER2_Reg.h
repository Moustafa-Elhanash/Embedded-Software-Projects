/*
 * TIMER2_Reg.h
 *
 * Created: 19/02/2024 07:13:22 م
 *  Author: moustafa
 */ 


#ifndef TIMER2_REG_H_
#define TIMER2_REG_H_

#define  TCCR2       (*(volatile uint8*)(0X45))   /*Timer/Counter 2 control register */
#define  TCCR2_FOC2   7
#define  TCCR2_WGM20  6                           /*waveform generation mode bit 0*/
#define  TCCR2_COM21  5
#define  TCCR2_COM20  4
#define  TCCR2_WGM21  3                           /*waveform generation mode bit 1*/

#define  TCNT2       (*(volatile uint8*)(0X44))   /*Timer/Counter 2 register */

#define  OCR2        (*(volatile uint8*)(0X43))   /*Timer/Counter 2 Output compare register */

#define  TIMSK       (*(volatile uint8*)(0X59))   /*Timer mask Register */
#define  TIMSK_TOIE2   6                          /*Timer2 overflow interrupt enable*/
#define  TIMSK_OCIE2   7                          /*Timer2 output compare interrupt enable*/

#define  TIFR        (*(volatile uint8*)(0X58))   /*Timer/Counter  interrupt flag register */
#define  TIFR_TOV2     6                          /*output compare flag*/
#define  TIFR_OCF2     7                          /*overflow flag*/






#endif /* TIMER2_REG_H_ */