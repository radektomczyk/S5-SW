#include "LCD.h"

	int main()
	{
		DDRC = 0xFF;
		LCD_Init(&PORTC);			/* Initialization of LCD*/
		DDRA = 0xF0;
		initKeyboard(&PORTA);		/* Initialization of keypad*/
		
		LCD_String("Systemy");
		//LCD_Command(0xC0);
		ustawKursor(1,0);
		LCD_String("Wbudowane");
		_delay_ms(1000);
		LCD_Clear();
		LCD_String_xy(0,0,"Klawisz: (klawa)");
		_delay_ms(1000);
		czysc_y(0,9);
		while(1){
			//LCD_Command(0xC0);
			//LCD_Char(keyfind());
			
			ustawKursor(0,9);
			LCD_Char(keyfind());
			//ustawKursor(1,1);
			//LCD_Char(keyfind());
		}
	}
	/*


	*/