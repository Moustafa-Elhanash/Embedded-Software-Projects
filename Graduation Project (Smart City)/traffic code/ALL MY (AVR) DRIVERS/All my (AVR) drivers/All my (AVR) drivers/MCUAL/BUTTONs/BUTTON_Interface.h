/*
 * BUTTON_Interface.h
 *
 * Created: 23/11/2023 06:50:18 م
 *  Author: moustafa elhanash
 */ 


#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_

ERROR_STATE_t BUTTON_INIT(const BUTTON_CONFIG_t *button);

uint8 BUTTON_READ(const BUTTON_CONFIG_t *button,ERROR_STATE_t  *error_state);


#endif /* BUTTON_INTERFACE_H_ */