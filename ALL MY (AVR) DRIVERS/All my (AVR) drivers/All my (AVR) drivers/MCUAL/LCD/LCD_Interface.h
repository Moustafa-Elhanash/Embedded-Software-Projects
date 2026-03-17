/*
 * LCD_Interface.h
 *
 * Created: 26/11/2023 07:29:57 م
 *  Author: Moustafa
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_WRITE_COMMAND(uint8 Command);

void LCD_WRITE_CHAR(uint8 Data);

void LCD_INIT(void);

ERROR_STATE_t LCD_WRITE_STRING(const char *string);


void LCD_WRITE_NUMBER(uint32 number);

void LCD_WRITE_FLOAT(float32 Fnumber);

void LCD_CLEAR_SCREEN(void);

void LCD_SET_CURSOR(uint8 row, uint8 column);

/************************************************************************/
/* EXTRA FUNCTIONS                                                                     */
/************************************************************************/
void LCD_WRITE_CUSTOM_CHAR(uint8 *Char_Array, uint8 BlockNumber,uint8 X_Position ,uint8 Y_Position );

/************************************************************************/
/*   from another drivers-------> assistant functions                                                                     */
/************************************************************************/

void reverse(char* str, int length);

int intToStr(int x, char str[], int d);

void ftoa(float n, char* res, int afterpoint);



#endif /* LCD_INTERFACE_H_ */