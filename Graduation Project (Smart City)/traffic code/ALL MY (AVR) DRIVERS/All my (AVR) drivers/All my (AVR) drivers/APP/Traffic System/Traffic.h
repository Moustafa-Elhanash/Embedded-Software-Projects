/*
 * Traffic.h
 *
 * Created: 15/02/2024 02:48:51 م
 *  Author: Moustafa 
 */ 


#ifndef TRAFFIC_H_
#define TRAFFIC_H_


#include "ALL_HIGH_LAYER_FILES.h"
/* for external interrupts int0, int1, int2 */
void ISR2(void);
void ISR1(void);
void ISR0(void);
/* for ADC */
void ADC_NOTIFICATION(void);
/* for timer ctc interrupt */
void TIMER0_CTC_ISR(void); 
/* for timer ctc interrupt */
void TIMER2_CTC_ISR(void);

void TRAFFIC_INIT(void);
void TRAFFIC_START(void);


#endif /* TRAFFIC_H_ */