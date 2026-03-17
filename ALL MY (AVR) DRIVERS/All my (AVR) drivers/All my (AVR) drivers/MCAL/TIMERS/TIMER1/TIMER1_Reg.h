/*
 * TIMER1_Reg.h
 *
 * Created: 20/02/2024 04:27:21 م
 *  Author: moustafa
 */ 


#ifndef TIMER1_REG_H_
#define TIMER1_REG_H_

#define TCCR1A			(*(volatile uint8*)(0X4F))
#define TCCR1B			(*(volatile uint8*)(0X4E))
#define TCNT1H          (*(volatile uint8*)(0X4D))
#define TCNT1L          (*(volatile uint8*)(0X4C))
#define TCNT1			(*(volatile uint16*)(0X4C))  /* u16 for HIGH & LOW */
#define OCR1AL          (*(volatile uint8*)(0X4A))
#define OCR1AH          (*(volatile uint8*)(0X4B))
#define OCR1A			(*(volatile uint16*)(0X4A))
#define OCR1BL          (*(volatile uint8*)(0X48))
#define OCR1BH          (*(volatile uint8*)(0X49))
#define OCR1B			(*(volatile uint16*)(0X48))
#define ICR1H           (*(volatile uint8*)(0X47))
#define ICR1L           (*(volatile uint8*)(0X46))
#define ICR1			(*(volatile uint16*)(0X46))



#endif /* TIMER1_REG_H_ */