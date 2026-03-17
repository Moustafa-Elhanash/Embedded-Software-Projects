/*
 * SEVEN_SEGMENT_Interface.h
 *
 * Created: 23/11/2023 09:03:01 م
 *  Author: moustafa 
 */ 


#ifndef SEVEN_SEGMENT_INTERFACE_H_
#define SEVEN_SEGMENT_INTERFACE_H_

void SEVEN_SEGMENT_INIT(GPIO_PORT_t port);
void SEVEN_SEGMENT_DISPLAY_NUMBER(GPIO_PORT_t port,uint8 Number);
void SEVEN_SEGMENT_DISPLAY_CHAR(GPIO_PORT_t port,uint8 Letter);
void SEVEN_SEGMENT_STOP(GPIO_PORT_t port);




#endif /* SEVEN_SEGMENT_INTERFACE_H_ */