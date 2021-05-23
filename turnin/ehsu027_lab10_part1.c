/*	Author: Evan Hsu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	Video link:
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "../header/keypad.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	unsigned char x;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
    /* Insert your solution below */
    while (1) {
	x = GetKeypadKey();
	switch (x) {
		case '\0': PORTB = 0x1F; break;
		case '1': PORTB = 0x81; break;
		case '2': PORTB = 0x82; break;
		case '3': PORTB = 0x83; break;
		case '4': PORTB = 0x84; break;
		case '5': PORTB = 0x85; break;
		case '6': PORTB = 0x86; break;
		case '7': PORTB = 0x87; break;
		case '8': PORTB = 0x88; break;
		case '9': PORTB = 0x89; break;
		case 'A': PORTB = 0x8A; break;
		case 'B': PORTB = 0x8B; break;
		case 'C': PORTB = 0x8C; break;
		case 'D': PORTB = 0x8D; break;
		case '*': PORTB = 0x8E; break;
		case '0': PORTB = 0x80; break;
		case '#': PORTB = 0x8F; break;
		default: PORTB = 0x1B; break;
	}
    }
    return 1;
}
