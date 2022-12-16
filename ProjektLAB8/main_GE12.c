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

 void LCDClearScreenV2(void) { 
  
  long i; // loop counter 
  
  // Row address set (command 0x2B) 
  WriteSpiCommand(PASET); //PASET NA PAGEADDRSET
  WriteSpiData(0); 
  WriteSpiData(131); 
  
  // Column address set (command 0x2A) 
  WriteSpiCommand(CASET); //CASET na COLADDRSET
  WriteSpiData(0); 
  WriteSpiData(131); 
  
  // set the display memory to BLACK 
  WriteSpiCommand(RAMWR); //RAMWR na MEMWRITE
  for(i = 0; i < ((132 * 132) / 2); i++) { 
  WriteSpiData((GREEN >> 4) & 0xFF); 
  WriteSpiData(((GREEN & 0xF) << 4) | ((GREEN >> 8) & 0xF)); 
  WriteSpiData(GREEN & 0xFF); 
  } 
 }

void delay(int n) __attribute__ ((section(".fast")));

void delay(int n){
  volatile int i;
  for(i=300*n;i>0;i--)
  {
    __asm__("nop");
  }
}

void LCDBlindTextV2(int x0, int y0, int x1, int y1, int cColor) {
// loop counter
int i;
// Row address set (command 0x2B)
WriteSpiCommand(PASET);
WriteSpiData(x0);
WriteSpiData(x0+x1);
// Column address set (command 0x2A)
WriteSpiCommand(CASET);
WriteSpiData(y0);
WriteSpiData(y0+y1);

WriteSpiCommand(RAMWR);
for(i = 0; i < ((132*132)/2 ); i++) {
 WriteSpiData((cColor >> 4) & 0xFF);
 WriteSpiData(((cColor & 0xF) << 4) | ((cColor >> 8) & 
0xF));
 WriteSpiData(cColor & 0xFF);
}
}

int main (){
PMC_PCER=PMC_PCER_PIOB;
PMC_PCER=PMC_PCER_PIOA;
PIOB_OER=LCD_BACKLIGHT;
PIOB_PER=LCD_BACKLIGHT;

InitLCD(); //inicjalizacja LCD
SetContrast(30);
LCDSettings(); //ustawienie LCD
LCDClearScreenV2(); // wyczyszczenie ekranu
//LCDWrite130x130bmp(); //wyœwietlenie BMP (zdef w pliku bmp.h)
PIOB_SODR|=LCD_BACKLIGHT; // ustawienie podœwietlenia na 1


while(1)
{
  if((PIOB_PDSR & SW_1)==0)
  {
    PIOB_SODR |= LCD_BACKLIGHT;
    LCDClearScreenV2(); // Wyczyszczenie ekranu
    LCDPutStr("SW1",110,10,LARGE,WHITE,BLACK);
    LCDBlindTextV2(4,80,10,90,WHITE);
  }
  if((PIOB_PDSR & SW_2)==0)
  {
    PIOB_SODR |= LCD_BACKLIGHT;
    LCDClearScreenV2(); // Wyczyszczenie ekranu
    LCDPutStr("SW2",110,100,LARGE,WHITE,BLACK);
    LCDBlindTextV2(4,80,10,90,WHITE);
  }
  
  if((PIOA_PDSR & UP)==0)
  {
    PIOB_SODR |= LCD_BACKLIGHT;
    LCDClearScreenV2(); // Wyczyszczenie ekranu
    LCDPutStr("UP",15,60,LARGE,WHITE,BLACK);
    LCDBlindTextV2(4,80,10,90,WHITE);
  }
  if((PIOA_PDSR & DOWN)==0)
  {
    PIOB_SODR |= LCD_BACKLIGHT;
    LCDClearScreenV2(); // Wyczyszczenie ekranu
    LCDPutStr("DOWN",110,50,LARGE,WHITE,BLACK);
    LCDBlindTextV2(4,80,10,90,WHITE);
  }
  if((PIOA_PDSR & LEFT)==0)
  {
    PIOB_SODR |= LCD_BACKLIGHT;
    LCDClearScreenV2(); // Wyczyszczenie ekranu
    LCDPutStr("LEFT",60,10,LARGE,WHITE,BLACK);
    LCDBlindTextV2(4,80,10,90,WHITE);
  }
  if((PIOA_PDSR & RIGHT)==0)
  {
    PIOB_SODR |= LCD_BACKLIGHT;
    LCDClearScreenV2(); // Wyczyszczenie ekranu
    LCDPutStr("RIGHT",60,90,LARGE,WHITE,BLACK);
    LCDBlindTextV2(4,80,10,90,WHITE);
  }
  if((PIOA_PDSR & CENTER)==0)
  {
    PIOB_SODR |= LCD_BACKLIGHT;
    LCDClearScreenV2(); // Wyczyszczenie ekranu
    LCDPutStr("ENTER",60,50,LARGE,WHITE,BLACK);
    LCDBlindTextV2(4,80,10,90,WHITE);
  }
}
return 0;
}