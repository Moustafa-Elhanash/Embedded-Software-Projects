/*
 * RELAY_Interface.h
 *
 * Created: 25/11/2023 06:25:08 م
 *  Author: MOUSTAFA
 */ 


#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

void RELAY_INIT(const RELAY_CONFIG_t *relay);
void RELAY_ON(const RELAY_CONFIG_t *relay);
void RELAY_OFF(const RELAY_CONFIG_t *relay);



#endif /* RELAY_INTERFACE_H_ */