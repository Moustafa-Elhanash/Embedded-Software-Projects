


#ifndef AVR_ADDRESS_H_
#define AVR_ADDRESS_H_
/*DIO*/
#define PORTA (*(volatile uint8_t*)(0X3B))
#define DDRA  (*(volatile uint8_t*)(0X3A))
#define PINA  (*(volatile uint8_t*)(0X39))

#define PORTB (*(volatile uint8_t*)(0X38))
#define DDRB  (*(volatile uint8_t*)(0X37))
#define PINB  (*(volatile uint8_t*)(0X36))

#define PORTC (*(volatile uint8_t*)(0X35))
#define DDRC  (*(volatile uint8_t*)(0X34))
#define PINC  (*(volatile uint8_t*)(0X33))

#define PORTD (*(volatile uint8_t*)(0X32))
#define DDRD  (*(volatile uint8_t*)(0X31))
#define PIND  (*(volatile uint8_t*)(0X30))
/*DIO*/

//Timer
#define TCCR0 (*(volatile uint8_t*)(0x53))
#define TCNT0 (*(volatile uint8_t*)(0x52))
#define TIFR (*(volatile uint8_t*)(0x58))
#define TIMSK (*(volatile uint8_t*)(0x59))



// Interrupt REGISTERS

#define SREG (*(volatile uint8_t*)(0x5F))
#define GICR (*(volatile uint8_t*)(0x5B))
#define MCUCR (*(volatile uint8_t*)(0x55))



#endif 