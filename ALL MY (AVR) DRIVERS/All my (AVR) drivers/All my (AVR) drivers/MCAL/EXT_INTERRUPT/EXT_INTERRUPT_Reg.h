/*
 * EXT_INTERRUPT_Reg.h
 *
 * Created: 11/12/2023 07:21:00 م
 *  Author: moustafa
 */ 


#ifndef EXT_INTERRUPT_REG_H_
#define EXT_INTERRUPT_REG_H_

#define GICR          (*(volatile uint8*)(0X5B))    /* General interrupt control register */
#define GICR_INT1       7                           /* INT1 PIE BIT */
#define GICR_INT0       6							/* INT0 PIE BIT */
#define GICR_INT2       5							/* INT2 PIE BIT */

#define GIFR          (*(volatile uint8*)(0X5A))
#define GIFR_INTF1      7                           /* INT1 FLAG BIT */
#define GIFR_INTF0      6						    /* INT0 FLAG BIT */
#define GIFR_INTF2      5						    /* INT2 FLAG BIT */

#define MCUCR         (*(volatile uint8*)(0X55))    /* MCU CONTROL REGISTER */
#define MCUCR_ISC11     3                           /* Interrupt 1 sense control bit 1*/
#define MCUCR_ISC10     2                           /* Interrupt 1 sense control bit 0*/
#define MCUCR_ISC01     1							/* Interrupt 0 sense control bit 1*/
#define MCUCR_ISC00     0							/* Interrupt 0 sense control bit 0*/

#define MCUCSR        (*(volatile uint8*)(0X54))    /* MCU CONTROL & STATUS REGISTER */
#define MCUCSR_ISC2     6                           /* Interrupt 2 sense control bit */

#define SREG          (*(volatile uint8*)(0X5F))    /* status register */
#define SREG_I          7                           /* Global interrupt enable bit */





#endif /* EXT_INTERRUPT_REG_H_ */