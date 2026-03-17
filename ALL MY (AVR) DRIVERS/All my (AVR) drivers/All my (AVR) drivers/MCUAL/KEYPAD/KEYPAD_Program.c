/*
 * KEYPAD_Program.c
 *
 * Created: 05/12/2023 03:53:51 م
 *  Author: Moustafa El-hanash
 */ 

#include "KEYPAD_Private.h"

void KEYPAD_INIT(void)
{
	/* define the direction of row pins (input)*/
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_ROW0_PIN,GPIO_INPUT);
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_ROW1_PIN,GPIO_INPUT);
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_ROW2_PIN,GPIO_INPUT);
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_ROW3_PIN,GPIO_INPUT);
	/* set the row pins as pull up */
	GPIO_SETPIN_PULLUP(KEYPAD_PORT,KEYPAD_ROW0_PIN);
	GPIO_SETPIN_PULLUP(KEYPAD_PORT,KEYPAD_ROW1_PIN);
	GPIO_SETPIN_PULLUP(KEYPAD_PORT,KEYPAD_ROW2_PIN);
	GPIO_SETPIN_PULLUP(KEYPAD_PORT,KEYPAD_ROW3_PIN);
	/* define the direction of column pins (output)*/
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_COLUMN0_PIN,GPIO_OUTPUT);
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_COLUMN1_PIN,GPIO_OUTPUT);
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_COLUMN2_PIN,GPIO_OUTPUT);
	GPIO_SETPIN_DIRECTION(KEYPAD_PORT,KEYPAD_COLUMN3_PIN,GPIO_OUTPUT);
	/* set the column pins as HIGH */
	GPIO_SETPIN_VALUE(KEYPAD_PORT,KEYPAD_COLUMN0_PIN,GPIO_HIGH);
	GPIO_SETPIN_VALUE(KEYPAD_PORT,KEYPAD_COLUMN1_PIN,GPIO_HIGH);
	GPIO_SETPIN_VALUE(KEYPAD_PORT,KEYPAD_COLUMN2_PIN,GPIO_HIGH);
	GPIO_SETPIN_VALUE(KEYPAD_PORT,KEYPAD_COLUMN3_PIN,GPIO_HIGH);
}

uint8 KEYPAD_GET_PRESSED_KEY(void)
{
	uint8 column_index=0 , row_index=0 , row_state=0 , pressed_button_val =KEYPAD_NOT_PRESSED;
	uint8 columns_array[NUMBER_OF_COLUMNS]={KEYPAD_COLUMN0_PIN,KEYPAD_COLUMN1_PIN,KEYPAD_COLUMN2_PIN,KEYPAD_COLUMN3_PIN};
	uint8 rows_array[NUMBER_OF_ROWS]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN};
		 uint8 keypad[4][4] =KEYPAD_BUTTON_VALUES;
		 
	for (column_index=0 ; column_index<NUMBER_OF_COLUMNS ; column_index++)
	{
		/* Activate the column */
		GPIO_SETPIN_VALUE(KEYPAD_PORT,columns_array[column_index],GPIO_LOW);
		for (row_index=0 ; row_index<NUMBER_OF_ROWS ;row_index++)
		{
			/* Read the row state */
			row_state=GPIO_READPIN_VALUE(KEYPAD_PORT,rows_array[row_index]);
			/* check if button is pressed */
			if (row_state == GPIO_LOW)
			{
				pressed_button_val=keypad[row_index][column_index];
				/* wait until the button is released (busy wait) */
				
				while(row_state == GPIO_LOW)
				{
					/* Read the row state */
					row_state=GPIO_READPIN_VALUE(KEYPAD_PORT,rows_array[row_index]);//////////
					
				}
				//break;
			    //_delay_ms(10);
			
			} 
			
		}
		/* Deactivate the column */
		GPIO_SETPIN_VALUE(KEYPAD_PORT,columns_array[column_index],GPIO_HIGH);
	}
    return pressed_button_val;
}