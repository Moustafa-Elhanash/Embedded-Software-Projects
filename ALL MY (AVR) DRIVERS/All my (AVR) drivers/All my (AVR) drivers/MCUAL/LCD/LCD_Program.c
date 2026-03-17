/*
 * LCD_Program.c
 *
 * Created: 26/11/2023 07:28:32 م
 *  Author: Moustafa
 */ 

#include "LCD_Private.h"

static void SetHalfDataPort(uint8 Data)
{
	uint8 DataPins[4] ={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN};
	uint8 counter=0;
	for (counter=0 ; counter<4; counter++)
	{
		GPIO_SETPIN_VALUE(LCD_DATA_PORT,DataPins[counter],GET_BIT(Data,counter));
	}
		
	
}

static void SendEnablePulse(void)
{
	GPIO_SETPIN_VALUE(LCD_CONTROL_PORT,LCD_EN_PIN,GPIO_HIGH);
	_delay_ms(2);
	GPIO_SETPIN_VALUE(LCD_CONTROL_PORT,LCD_EN_PIN,GPIO_LOW);
}

void LCD_WRITE_COMMAND(uint8 Command)
{
	/* set RS to 0 to command */
	GPIO_SETPIN_VALUE(LCD_CONTROL_PORT,LCD_RS_PIN,GPIO_LOW);
	/* set RW to 0 to Write */
	GPIO_SETPIN_VALUE(LCD_CONTROL_PORT,LCD_RW_PIN,GPIO_LOW);
	
	#if (LCD_MODE == EIGHT_BIT_MODE)
/* Send command */
GPIO_WRITE_ON_PORT(LCD_DATA_PORT,Command);
/* Send enable pulse */
SendEnablePulse();

#elif (LCD_MODE == FOUR_BIT_MODE)
/* Send High order data bits First */
SetHalfDataPort(Command>>4);
/* Send enable pulse */
SendEnablePulse();
/* Send low order data bits  */
SetHalfDataPort(Command);
/* Send enable pulse */
SendEnablePulse();



#endif
	
	
}

void LCD_WRITE_CHAR(uint8 Data)
{
		/* set RS to 1 to send data */
		GPIO_SETPIN_VALUE(LCD_CONTROL_PORT,LCD_RS_PIN,GPIO_HIGH);
		/* set RW to 0 to Write */
		GPIO_SETPIN_VALUE(LCD_CONTROL_PORT,LCD_RW_PIN,GPIO_LOW);
		
		#if (LCD_MODE == EIGHT_BIT_MODE)
		/* Send data */
		GPIO_WRITE_ON_PORT(LCD_DATA_PORT,Data);
		/* Send enable pulse */
		SendEnablePulse();

		#elif (LCD_MODE == FOUR_BIT_MODE)
		/* Send High order data bits First */
		SetHalfDataPort(Data>>4);
		/* Send enable pulse */
		SendEnablePulse();
		/* Send low order data bits  */
		SetHalfDataPort(Data);
		/* Send enable pulse */
		SendEnablePulse();
		#endif
}

void LCD_INIT(void)
{
	
	
	/* 1- wait for 30 ms after power on */
	_delay_ms(40);
		#if (LCD_MODE == EIGHT_BIT_MODE)
		GPIO_SETPORT_DIRECTION(LCD_DATA_PORT,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_CONTROL_PORT,LCD_RS_PIN,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_CONTROL_PORT,LCD_RW_PIN,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_CONTROL_PORT,LCD_EN_PIN,GPIO_OUTPUT);
        /* 2- Function set command : 2 lines , font-> 5x8 */
        LCD_WRITE_COMMAND(0b00111100); //0b00111000
        /* 3- Display on / off control : display on , cursor off ,blink cursor off */
        LCD_WRITE_COMMAND(0b00001100);
        /* 4- LCD clear */
        LCD_WRITE_COMMAND(1);
		
		#elif (LCD_MODE == FOUR_BIT_MODE)
		GPIO_SETPIN_DIRECTION(LCD_CONTROL_PORT,LCD_RS_PIN,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_CONTROL_PORT,LCD_RW_PIN,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_CONTROL_PORT,LCD_EN_PIN,GPIO_OUTPUT);
		
		GPIO_SETPIN_DIRECTION(LCD_DATA_PORT,LCD_D4_PIN,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_DATA_PORT,LCD_D5_PIN,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_DATA_PORT,LCD_D6_PIN,GPIO_OUTPUT);
		GPIO_SETPIN_DIRECTION(LCD_DATA_PORT,LCD_D7_PIN,GPIO_OUTPUT);
		SetHalfDataPort(0b0010);
		SendEnablePulse();
		
		SetHalfDataPort(0b0010);
		SendEnablePulse();
		
		SetHalfDataPort(0b1000);
		SendEnablePulse();
		 /* 3- Display on / off control : display on , cursor off ,blink cursor off */
		 LCD_WRITE_COMMAND(0b00001100);
		 /* 4- LCD clear */
		 LCD_WRITE_COMMAND(1);
		
		#endif
	
}

ERROR_STATE_t LCD_WRITE_STRING(const char *string)
{
	ERROR_STATE_t error_state = F_NOK;
	if (NULL == string)
	{
		error_state=F_NULL_POINTER;
	} 
	else
	{
		uint8 counter=0;
		while('\0' != string[counter])
		{
			LCD_WRITE_CHAR(string[counter]);
			counter++;
		}
		error_state=F_OK;
	}
	return error_state;
}


void LCD_WRITE_NUMBER(uint32 number)
{
	char str[16];
	itoa(number,str,16);
	/*itoa(number, (char*)str, strlen(str));*/
	LCD_WRITE_STRING(str);
}

void LCD_WRITE_FLOAT(float32 Fnumber)
{
	char Float_num[10];
	ftoa(Fnumber, (char*)Float_num,3);   // 3 numbers after dot
	LCD_WRITE_STRING(Float_num);
}

void LCD_CLEAR_SCREEN(void)
{
	LCD_WRITE_COMMAND(1);
}

void LCD_SET_CURSOR(uint8 row, uint8 column)
{
	uint8 Loc_Row0 = 0x80;
	uint8 Loc_Row1 = 0xC0;
	switch(row)
	{
		case 0:
		Loc_Row0 += column;
		LCD_WRITE_COMMAND(Loc_Row0);
		break;
		case 1:
		Loc_Row1 += column;
		LCD_WRITE_COMMAND(Loc_Row1);
		break;
		default:
		Loc_Row0 += column;
		LCD_WRITE_COMMAND(Loc_Row0);
		break;
	}
}

/************************************************************************/
/* EXTRA FUNCTIONS                                                                     */
/************************************************************************/

void LCD_WRITE_CUSTOM_CHAR(uint8 *Char_Array, uint8 BlockNumber,uint8 X_Position ,uint8 Y_Position )  
{
	uint8 counter = 0;
	/* Calculate the starting address in the CGRAM for the required pattern number */
	uint8 CGRAM_Add = BlockNumber * 8;
	/* Set bit number 6 and clear bit number 7 , for set CGRAM Address command */
	SET_BIT(CGRAM_Add,6);
	
	/* set CGRAM Address command */
	LCD_WRITE_COMMAND(CGRAM_Add);
	/* draw the pattern inside the CGRAM */
	for (counter = 0; counter < 8; counter++)
	{
		LCD_WRITE_CHAR(Char_Array[counter]);
	}
	/* go back to DDRAM to display the pattern */
	LCD_SET_CURSOR(X_Position,Y_Position);
	
	/* Display the drawn pattern */
	LCD_WRITE_CHAR(BlockNumber);
}


/************************************************************************/
/*   from another drivers -------> assistant functions                                                            */
/************************************************************************/

void reverse(char* str, int length)
{
	int i = 0, j = length - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}


int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}
