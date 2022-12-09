#include <targets\AT91SAM7.h>
#include "pcf8833u8_lcd.h"
int main (){

InitLCD(); // Inicjalizacja ekranu LCD
SetContrast(30);
LCDClearScreen(); // Wyczyszczenie ekranu

LCDPutStr("Imie i Nazwisko", 15, 10, LARGE, BLACK, WHITE); // Wyświetlenie na LCD imienia i nazwiska
LCDPutStr("Grupa: ", 30, 30, LARGE, BLACK, WHITE); // Wyświetlenie grupy w kolejnej linii 
Delaya(10000000); // Opóźnienie 5 sekund
LCDClearScreen(); // Wyczyszczenie ekranu
LCDWrite130x130bmp(); // Wyświetlenie obrazu na LCD


}