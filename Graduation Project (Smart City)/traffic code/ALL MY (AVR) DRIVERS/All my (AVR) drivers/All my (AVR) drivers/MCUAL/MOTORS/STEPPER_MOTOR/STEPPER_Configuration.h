/*
 * STEPPER_Configuration.h
 *
 * Created: 08/12/2023 06:33:39 م
 *  Author: MOUSTAFA
 */ 


#ifndef STEPPER_CONFIGURATION_H_
#define STEPPER_CONFIGURATION_H_

#include "ALL_LOW_LAYER_FILES.h"

#define STEPPER                 PORTD
#define STEPPER_PORT            GPIO_PORTD

#define STEPPER_COIL_A_PLUS     GPIO_PIN0    //IN1
#define STEPPER_COIL_A_MINUS    GPIO_PIN1	 //IN2

#define STEPPER_COIL_B_PLUS     GPIO_PIN2	 //IN3
#define STEPPER_COIL_B_MINUS    GPIO_PIN3	 //IN4

typedef enum{
	Half_step =0,
	Full_step
	
	}STEP_TYPE_t;
	
typedef enum{
	Step_CW=0,
	Step_CCW
	
	}STEP_DIRECTION_t;
	
typedef struct{
    GPIO_PORT_t stepper_port;
	GPIO_PIN_t A_Plus_Pin;
	GPIO_PIN_t A_Minus_Pin;
	GPIO_PIN_t B_Plus_Pin;
	GPIO_PIN_t B_Minus_Pin;
	STEP_TYPE_t step_type;
	STEP_DIRECTION_t rotation_direction;
	
	}STEPPER_CONFIG_t;


#endif /* STEPPER_CONFIGURATION_H_ */