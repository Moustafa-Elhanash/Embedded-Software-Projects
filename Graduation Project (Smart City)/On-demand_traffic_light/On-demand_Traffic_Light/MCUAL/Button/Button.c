

#include "Button.h"

void Button_Initialization(void)
{
 DIO_SETPIN_DIRECTION(Button_prt,Button_pin,DIO_INPUT);
}
uint8_t Button_Read(void)
{
 uint8_t BTN_VAL = DIO_LOW;
 uint8_t val = 0 ;
 _delay_ms(10);
 BTN_VAL = DIO_READPIN_VALUE(Button_prt,Button_pin);
 return BTN_VAL;
}

