/*
 * EXT_INTERRUPT_Interface.h
 *
 * Created: 11/12/2023 07:22:01 م
 *  Author: moustafa
 */ 


#ifndef EXT_INTERRUPT_INTERFACE_H_
#define EXT_INTERRUPT_INTERFACE_H_

void EXT_INTERRUPT_INIT(void);

void EXT_ENABLE_GLOBAL(void);

void EXT_DISABLE_GLOBAL(void);

ERROR_STATE_t EXT_SET_CALL_BACK(uint8 int_number,void(*ptr_to_callBackFunction)(void));

/*ERROR_STATE_t EXT_SET_SENSE_CONTROl(uint8 int_num,uint8 sense);*/





#endif /* EXT_INTERRUPT_INTERFACE_H_ */