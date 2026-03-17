/*
 * Timer2_Interface.h
 *
 * Created: 19/02/2024 07:12:55 م
 *  Author: win10
 */ 


#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

void TIMER2_INIT(void);

ERROR_STATE_t TIMER2_SET_CALL_BACK(uint8 interrupt_type,void(*Ptr_To_CallBackFunc)(void));

void TIMER2_SET_PRELOAD(uint8 Preload);

void TIMER2_SET_CTC (uint8 CTC_val);

uint8 TIMER2_GetTimerCounterValue (void);

void TIMER2_STOP_COUNTING(void);




#endif /* TIMER2_INTERFACE_H_ */