/*
 * BIT_MATH.h
 *
 * Created: 20/11/2023 07:18:41 م
 *  Author: moustafa elhanash
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG,BIT) REG|=(1<<BIT)
#define CLR_BIT(REG,BIT) REG&=~(1<<BIT)
#define TGL_BIT(REG,BIT) REG^=(1<<BIT)
#define GET_BIT(REG,BIT) ((REG>>BIT)&1)
#define ASSIGN_BIT(REG,BIT,VAL)  (REG = (REG&(~(1<<BIT)))|(VAL<<BIT))



#endif /* BIT_MATH_H_ */