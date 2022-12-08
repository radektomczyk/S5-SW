/*
 * LCD.h
 *
 * Created: 01.12.2022 16:13:24
 *  Author: Lenovo
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000UL			/* Define CPU Frequency e.g. here 1MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#define RS PB1				/* Define Register Select pin */
#define EN PB0 				/* Define Enable signal pin */

unsigned char colloc, rowloc;

void initKeyboard(volatile uint8_t *port);
char keyfind();
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data ); 
void LCD_Init (volatile uint8_t *port);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();
void ustawKursor(unsigned char x, unsigned char y );
void czysc_y(int8_t x, int8_t y);

#endif /* LCD_H_ */