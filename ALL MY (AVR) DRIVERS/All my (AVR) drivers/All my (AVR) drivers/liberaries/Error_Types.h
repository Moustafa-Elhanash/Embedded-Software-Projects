/*
 * Error_Types.h
 *
 * Created: 20/11/2023 07:48:51 م
 *  Author: Moustafa El-hanash
 */ 


#ifndef ERROR_TYPES_H_
#define ERROR_TYPES_H_


//#define NULL 0

typedef enum{
	F_OK=0,
	F_NOK,
	F_NULL_POINTER,
	F_TIMEOUT,
	F_BUSY
	
	
	}ERROR_STATE_t;



#endif /* ERROR_TYPES_H_ */