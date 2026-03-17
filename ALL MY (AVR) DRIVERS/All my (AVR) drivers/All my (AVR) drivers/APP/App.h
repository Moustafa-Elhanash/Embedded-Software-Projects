/*
 * App.h
 *
 * Created: 21/11/2023 09:00:57 م
 *  Author: moustafa elhanash
 */ 


#ifndef APP_H_
#define APP_H_

#include "ALL_HIGH_LAYER_FILES.h"

	
void ISR2(void);
void ISR1(void);
void ISR0(void);
void ADC_NOTIFICATION(void);

void APP_INIT(void);
void APP_START(void);


#endif /* APP_H_ */