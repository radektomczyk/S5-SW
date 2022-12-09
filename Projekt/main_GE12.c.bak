#include <targets\AT91SAM7.h>
#include "pcf8833u8_lcd.h"
#define LCD_BACKLIGHT PIOB_SODR_P20
#define AUDIO_OUT PIOB_SODR_P19
#define SW_1 PIOB_SODR_P24
#define SW_2 PIOB_SODR_P25
#define UP PIOA_SODR_P9
#define CENTER PIOA_SODR_P15
#define LEFT PIOA_SODR_P7
#define DOWN PIOA_SODR_P8
#define RIGHT PIOA_SODR_P14

void delay(int n) __attribute__ ((section(".fast")));

void delay(int n)
{
  volatile int i;
  for(i=300*n;i>0;i--)
  {
    __asm__("nop");
  }
}

int main (){

/*InitLCD(); // Inicjalizacja ekranu LCD
SetContrast(30);
LCDClearScreen(); // Wyczyszczenie ekranu

LCDPutStr("Imie i Nazwisko", 15, 10, LARGE, BLACK, WHITE); // Wyœwietlenie na LCD imienia i nazwiska
LCDPutStr("Grupa: ", 30, 30, LARGE, BLACK, WHITE); // Wyœwietlenie grupy w kolejnej linii 
Delaya(10000000); // OpóŸnienie 5 sekund
LCDClearScreen(); // Wyczyszczenie ekranu
LCDWrite130x130bmp(); // Wyœwietlenie obrazu na LCD*/

PMC_PCER=PMC_PCER_PIOB;
PMC_PCER=PMC_PCER_PIOA;
PIOB_OER=LCD_BACKLIGHT | AUDIO_OUT;
PIOB_PER=LCD_BACKLIGHT | AUDIO_OUT;

InitLCD();
LCDSettings();
LCDClearScreen();
LCDPutStr("TEST",20,20,LARGE,BLACK,WHITE);
LCDPutStr("Radoslaw Tomczyk",20,20,LARGE,BLACK,WHITE);

while(1)
{
  if((PIOB_PDSR & SW_1)==0)
  {
    //PIOB_SODR |= LCD_BACKLIGHT;
    PIOB_SODR |= AUDIO_OUT;
    delay(5);
    PIOB_CODR |= AUDIO_OUT;
    delay(10);
  }
  if((PIOB_PDSR & SW_2)==0)
  {
    //PIOB_CODR |= LCD_BACKLIGHT;
    PIOB_SODR |= AUDIO_OUT;
    delay(10);
    PIOB_CODR |= AUDIO_OUT;
    delay(5);
  }
  
  if((PIOA_PDSR & UP)==0)
  {
    //PIOB_CODR |= LCD_BACKLIGHT;
    PIOB_SODR |= AUDIO_OUT;
    delay(10);
    PIOB_CODR |= AUDIO_OUT;
    delay(15);
  }
  if((PIOA_PDSR & DOWN)==0)
  {
    //PIOB_CODR |= LCD_BACKLIGHT;
    PIOB_SODR |= AUDIO_OUT;
    delay(20);
    PIOB_CODR |= AUDIO_OUT;
    delay(20);
  }
  
}
return 0;
}