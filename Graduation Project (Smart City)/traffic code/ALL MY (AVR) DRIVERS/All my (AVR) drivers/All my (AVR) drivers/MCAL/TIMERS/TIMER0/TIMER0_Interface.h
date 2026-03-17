/*
 * TIMER0_Interface.h
 *
 * Created: 15/02/2024 10:18:59 م
 *  Author: MOUSTAFA
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

void TIMER0_INIT(void);

ERROR_STATE_t TIMER0_SET_CALL_BACK(uint8 interrupt_type,void(*Ptr_To_CallBackFunc)(void));

void TIMER0_SET_PRELOAD(uint8 Preload);

void TIMER0_SET_CTC (uint8 CTC_val);

uint8 TIMER0_GetTimerCounterValue (void);

void TIMER0_STOP_COUNTING(void);

#endif /* TIMER0_INTERFACE_H_ */