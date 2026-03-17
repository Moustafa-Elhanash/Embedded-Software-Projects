/*
 * ADC_Reg.h
 *
 * Created: 03/02/2024 08:55:14 م
 *  Author: MOUSTAFA
 */ 


#ifndef ADC_REG_H_
#define ADC_REG_H_

#define  ADMUX       (*(volatile uint8*)(0X27))  /* ADC Multiplexer Selection Register */
#define  ADMUX_REFS1     7
#define  ADMUX_REFS0     6
#define  ADMUX_ADLAR     5


#define  ADCSRA      (*(volatile uint8*)(0x26))  /* ADC Control and Status Register */
#define  ADCSRA_ADEN     7
#define  ADCSRA_ADSC     6
#define  ADCSRA_ADATE    5
#define  ADCSRA_ADIF     4
#define  ADCSRA_ADIE     3

#define  ADCH        (*(volatile uint8*)(0x25))  /* ADC High byte */
#define  ADCL        (*(volatile uint8*)(0x24))  /* ADC Low byte */
#define  ADC_L_H     (*(volatile uint16*)(0x24))  /* ADC Low and High */
#define  SFIOR       (*(volatile uint8*)(0x50))  /* Special functional O Register */




#endif /* ADC_REG_H_ */