/*
 * DIO_Private.h
 *
 * Created: 9/20/2022 12:45:17 PM
 *  Author: User
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


#include "DIO_Configuration.h"



void DIO_SETPIN_DIRECTION(DIO_PORTS port , DIO_PINS pin ,DIO_STATUS status);
void DIO_SETPIN_VALUE(DIO_PORTS port , DIO_PINS pins , DIO_STATE state);
uint8_t DIO_READPIN_VALUE(DIO_PORTS port ,DIO_PINS pin);
void DIO_TOGPIN_VALUE(DIO_PORTS port ,DIO_PINS pin);
void DIO_SETPIN_PULLUP(DIO_PORTS port , DIO_PINS pin);


void DIO_SETPORT_DIRECTION(DIO_PORTS port , DIO_STATUS status);
void DIO_SETPORT_VALUE(DIO_PORTS port , DIO_STATE state);
uint8_t DIO_READPORT_VALUE(DIO_PORTS port);
void DIO_TOGPORT_VALUE(DIO_PORTS port);



#endif /* DIO_PRIVATE_H_ */