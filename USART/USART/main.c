#include <avr/io.h> // dolaczenie biblioteki we/wy
#include <avr/interrupt.h> // dolaczenie biblioteki obslugi przerwan
#define F_CPU 8000000UL // ustawienie czestotliwosci taktowania procesora
#define USART_BAUDRATE 9600 // okreslenie predkosci przesylania
#define UBRR_VALUE (( (F_CPU / (USART_BAUDRATE * 16UL)) ) -1) // wyznaczenie zawartosci rejestru UBRR

void USART_Init(void){
	UBRRH = (uint8_t)(UBRR_VALUE>>8); // wpisanie starszego bajtu
	UBRRL = (uint8_t)UBRR_VALUE; 	 // wpisanie mlodszego bajtu
	UCSRC |= (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);  // ramka 8b, brak parzystosci, 1 bit stopu
	UCSRB |= (1<<RXCIE) | (1<<RXEN) | (1<<TXEN);   // wlaczenie odbioru i transmisji
}

void USART_TxChar(unsigned char data){ // funkcja wysylajaca znak
	while(!(UCSRA & (1<<UDRE))); // czekaj dopoki wysylane sa dane
	UDR = data; // ustaw wartosc
}

void USART_TxString(char *string){ // funkcja wysylajaca string
	while(*string){ // dopoki string sie nie skonczy
		USART_TxChar(*string++); // wyswietl string
	}
}

uint8_t USART_RxChar(){ // funkcja odbierajaca znak
	while((UCSRA & (1<<RXC)) == 0); // czekaj na odbior
	return UDR; // zwroc dane
}

void zadanie1(){
	USART_Init(); // inicjalizuj port
	USART_TxString("\r\nRados³aw Tomczyk\r\n"); // wyswietl linijke
	//USART_TxChar('\r'); // wyslij znak
}

void zadanie2(){
	USART_Init(); // inicjalizuj port
	
	while(1){
		USART_TxString("\r\nWcisnij klawisz [r]: "); // wyswietl tekst
		char temp = USART_RxChar(); // odbierz znak
		if ((temp == 'R') || (temp == 'r')) { // sprawdzenie znaku
			USART_TxString("\r\nWprowadzono prawidlowy znak!\r\n"); // wyswielt komunikat
		}
		else {
			USART_TxString("\r\nWprowadzono nieprawidlowy znak!\r\n"); // wyswielt komunikat
		}
	} // mozna wrzucic do petli zeby ciagle wciskac znak
}

void diodControl(){ // funkcja kontroli diod
	char znak; // zmienna char
	znak = USART_RxChar(); // przypisz do zmiennej odebrany znak
	switch (znak){
		case '1': PORTA ^= 0b00000010; break; // dioda 1
		case '2': PORTA ^= 0b00000100; break; // dioda 2
		case '3': PORTA ^= 0b00001000; break; // dioda 3
		case '4': PORTA ^= 0b00010000; break; // dioda 4
		case '5': PORTA ^= 0b00100000; break; // dioda 5
		case '6': PORTA ^= 0b01000000; break; // dioda 6
		case '7': PORTA ^= 0b10000000; break; // dioda 7
		case 'c': PORTA &= (0x01); break; // zgas diody oprocz diody 0
		case 's': PORTA |= (0xFE); break; // zapal diody oprocz diody 0
		default:
			USART_TxString("\r\nBledny znak!\r\n"); // wyswietl komunikat
			USART_TxString("\r\nWcisnij przycisk 1-7: "); // wyswietl komunikat
	}
}

volatile int licznik=0;
ISR(TIMER0_COMP_vect){
	licznik++;
	if(licznik == 300){
		PORTA ^= (1 << PA0);
		licznik = 0;
	}
}

ISR(USART_RXC_vect) { //przerwanie od odbioru danej
	static char a; //zmienna pomocnicza
	//a = UDR; //zapis odebranej danej
	a ^= 0xFF; //operacja bitowa XOR
	UDR = a; //wys³anie danej zwrotnej
	UCSRA |= (1<<PA0);
}


void zadanie3(){
	DDRA = 0xFF; // ustaw port na wyjscie
	PORTA = 0x00; // ustaw stan
	
	TCCR0 |= (1 << WGM01) | (1 << COM00) | (1 << CS02); // preskaler 1024
	OCR0 = 80;
	TIMSK = (1 << OCIE0);
	sei();
	
	USART_Init(); // inicjalizuj port
	USART_TxString("\r\nWcisnij przycisk 1-7: "); // wyswietl komunikat
	
	while(1){
		diodControl(); // funkcja do obslugi diod w petli
	}
	
}

int main(void){
	//zadanie1();
	//zadanie2();
	zadanie3();
}
