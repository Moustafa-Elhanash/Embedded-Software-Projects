/*
 * LED_Interface.h
 *
 * Created: 21/11/2023 07:17:57 م
 *  Author: MOUSTAFA ELHANASH
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_
//#include "Error_Types.h"

ERROR_STATE_t LED_INIT(const LED_CONFIG_t *led);
ERROR_STATE_t LED_ON(const LED_CONFIG_t *led);
ERROR_STATE_t LED_OFF(const LED_CONFIG_t *led);
ERROR_STATE_t LED_TGL(const LED_CONFIG_t *led);


#endif /* LED_INTERFACE_H_ */