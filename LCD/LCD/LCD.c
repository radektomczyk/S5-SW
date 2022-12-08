/*
 * LCD.c
 *
 * Created: 01.12.2022 16:13:48
 *  Author: Lenovo
 */ 

#include "LCD.h"
#define LCD_Dir  DDRC			/* Define LCD data port direction */
#define LCD_Port PORTC			/* Define LCD data port */
#define KEY_PRT PORTA
#define KEY_DDR	DDRA
#define KEY_PIN	PINA

unsigned char keypad[4][4] = {	{'1','4','7','/'},
								{'2','5','8','0'},
								{'3','6','9','-'},
								{'A','B','C','D'}};

void initKeyboard(volatile uint8_t *port){
	*port = 0x0F;
}

char keyfind()
{
	while(1)
	{
		//KEY_DDR = 0xF0;           /* set port direction as input-output */
		//KEY_PRT = 0x0F;

		do
		{
			KEY_PRT &= 0x0F;      /* mask PORT for column read only */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F); /* read status of column */
		}while(colloc != 0x0F);
		
		do
		{
			do
			{
				_delay_ms(20);             /* 20ms key debounce time */
				colloc = (KEY_PIN & 0x0F); /* read status of column */
				}while(colloc == 0x0F);        /* check for any key press */
				
				_delay_ms (40);	            /* 20 ms key debounce time */
				colloc = (KEY_PIN & 0x0F);
			}while(colloc == 0x0F);

			/* now check for rows */
			KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 0;
				break;
			}

			KEY_PRT = 0xDF;		/* check for pressed key in 2nd row */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 1;
				break;
			}
			
			KEY_PRT = 0xBF;		/* check for pressed key in 3rd row */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 2;
				break;
			}

			KEY_PRT = 0x7F;		/* check for pressed key in 4th row */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F);
			if(colloc != 0x0F)
			{
				rowloc = 3;
				break;
			}
		}

		if(colloc == 0x0E)
		return(keypad[rowloc][0]);
		else if(colloc == 0x0D)
		return(keypad[rowloc][1]);
		else if(colloc == 0x0B)
		return(keypad[rowloc][2]);
		else
		return(keypad[rowloc][3]);
	}
	void LCD_Command( unsigned char cmnd )
	{
		LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);/* Sending upper nibble */
		LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
		LCD_Port |= (1<<EN);		/* Enable pulse */
		_delay_us(1);
		LCD_Port &= ~ (1<<EN);
		_delay_us(200);
		LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);/* Sending lower nibble */
		LCD_Port |= (1<<EN);
		_delay_us(1);
		LCD_Port &= ~ (1<<EN);
		_delay_ms(2);

	}

	void LCD_Char( unsigned char data )
	{
		LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
		LCD_Port |= (1<<RS);		/* RS=1, data reg. */
		LCD_Port|= (1<<EN);
		_delay_us(1);
		LCD_Port &= ~ (1<<EN);

		_delay_us(200);

		LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
		LCD_Port |= (1<<EN);
		_delay_us(1);
		LCD_Port &= ~ (1<<EN);
		_delay_ms(2);
	}

	void LCD_Init (volatile uint8_t *port)			/* LCD Initialize function */
	{
		*port = 0xFF;			/* Make LCD port direction as o/p */
		_delay_ms(20);			/* LCD Power ON delay always >15ms */
		
		LCD_Command(0x02);		/* send for 4 bit initialization of LCD  */
		LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
		LCD_Command(0x0c);              /* Display on cursor off*/
		LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
		LCD_Command(0x01);              /* Clear display screen*/
		_delay_ms(2);
	}


	void LCD_String (char *str)		/* Send string to LCD function */
	{
		int i;
		for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
		{
			LCD_Char (str[i]);
		}
	}

	void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
	{
		if (row == 0 && pos<16)
		LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
		else if (row == 1 && pos<16)
		LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
		LCD_String(str);		/* Call LCD string function */
	}

	void LCD_Clear()
	{
		LCD_Command (0x01);		/* Clear display */
		_delay_ms(2);
		LCD_Command (0xC0);		/* Cursor at home position */
	}

	void ustawKursor(unsigned char x, unsigned char y )
	{
		LCD_Port &=~(1<<RS);
		LCD_Command((x*0x40+y) | 0x80);
		LCD_Port |= (1<<RS);
		_delay_ms(5);
	}
	void czysc_y(int8_t x, int8_t y)
	{
		while(y<16)
		{
			ustawKursor(x,y);
			LCD_Char(' ');
			y++;
			_delay_ms(50);
		}
		ustawKursor(x,y);
	}