/*
 * IR_Configuration.h
 *
 * Created: 20/03/2024 05:27:17 م
 *  Author: win10
 */ 


#ifndef IR_CONFIGURATION_H_
#define IR_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

typedef struct {
	GPIO_PORT_t ir_port;
	GPIO_PIN_t  ir_pin;
	
	}IR_CONFIG_t;
	
	



#endif /* IR_CONFIGURATION_H_ */