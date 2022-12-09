#include <targets/AT91SAM7.h>
#include "lcd.h"

#define LCD_BACKLIGHT PIOB_SODR_P20 
#define AUDIO_OUT PIOB_SODR_P19
#define SW_1 PIOB_SODR_P24
#define SW_2 PIOB_SODR_P25

__attribute__ ((section(".fast")))
void delay(int n) //procedura opoznienia 
{
volatile int i;

for(i=3000*n;i>0;i--)
{
__asm__("nop");
}
}



int main()
{
PMC_PCER=PMC_PCER_PIOB; //wlaczenie urzadzenia we/wy PIOB
PIOB_OER=LCD_BACKLIGHT | AUDIO_OUT; //OUTPUT ENABLE
PIOB_PER=LCD_BACKLIGHT | AUDIO_OUT; //PIO ENABLE 

InitLCD(); //inicjalizacja LCD
LCDSettings(); //ustawienie LCD
LCDClearScreen();
//LCDWrite130x130bmp(); //wyswietlenie BMP (zdef w pliku bmp.h)
LCDPutStr("TEST",20,20,LARGE,WHITE,BLACK) ;

while(1)
{

if ((PIOB_PDSR & SW_1)==0)
{
PIOB_SODR|=LCD_BACKLIGHT;  //ustawienie 1 
PIOB_SODR|=AUDIO_OUT;
delay(1);
PIOB_CODR|=AUDIO_OUT;
delay(1);
}

if ((PIOB_PDSR & SW_2)==0)
{
PIOB_CODR|=LCD_BACKLIGHT; //ustawienie 0 
PIOB_SODR|=AUDIO_OUT;
delay(5);
PIOB_CODR|=AUDIO_OUT;
delay(5);
}


}
return 0;
}