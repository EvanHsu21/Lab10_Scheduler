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
#include "../header/scheduler.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char combination[] = { '1', '2', '3', '4', '5' };
unsigned char i = 0;
unsigned char x;

enum KeyPad { K_Start, K_Press, K_Wait } K_State;
void KeypadSM() {
	x = GetKeypadKey();
	switch(K_State) {
		case K_Start:
			K_State = K_Wait;
		break;
		case K_Wait:
			if (x != '\0') {
				K_State = K_Press;
				PORTB = PORTB | 0x02;
			}
			else if (x == '\0') {
				K_State = K_Wait;
				PORTB = PORTB & 0xFD;
			}
		break;
		case K_Press:
			if (x != '\0') {
				K_State = K_Press;
				PORTB = PORTB | 0x02;
			}
			else if (x == '\0') {
				K_State = K_Wait;
				PORTB = PORTB & 0xFD;
			}
		break;
		default:
			K_State = K_Wait;
		break;
	}
}

/*
enum LockUnlock { L_Start, L_Correct, L_Incorrect, L_Finish } L_State;
void LockSM() {
	switch(L_State) {
		case L_Start:
			if (x == pattern[i]) {
				L_State = L_Correct;
				++i;
			}
			else if (x != pattern[i]) {
				L_State = L_Incorrect;
			}
		break;
		case L_Correct:
			if (x == pattern[i]) {
				L_State = L_Correct;
				++i;
			}
			else if (x != pattern[i]) {
				L_State = L_Incorrect;
			}
			else if (i == 5) {
				L_State = L_Finish;
			}
		break;
		case L_Incorrect:
			i = 0;
			L_State = L_Start;
		break;
		case L_Finish:
			if ((PINB & 0x80) == 0x00) {
				i = 0;
				L_State = L_Start;
			}
			else if ((PINB & 0x80) == 0x80) {
				L_State = L_Finish;
			}
		break;
	}
	switch(L_State) {
		case L_Start:
			PORTB = 0x00;
		break;
		case L_Correct:
			PORTB = 0x00;
		break;
		case L_Incorrect:
			PORTB = 0x00;
		break;
		case L_Finish:
			PORTB = 0x01;
		break;
		default:
		break;
	}
}
*/

enum SM_STATES { SM_SMStart, SM_Lock, SM_Reset, SM_Continue, SM_Unlock } SM_STATE;
        void Tick_Toggle() {
                switch(SM_STATE) {
                        case SM_SMStart:
                                SM_STATE = SM_Lock;		
                                break;
                        case SM_Lock:
				if (x == '\0') {
					SM_STATE = SM_Lock;
				}
				else if (x == combination[i]) {
					if (i == 4) {
						SM_STATE = SM_Unlock;
					}
					else if (i < 4) {
						SM_STATE = SM_Continue;
					}
				}
				else if (x != combination[i]) {
					SM_STATE = SM_Reset;
					i = 0;
				}
                        break;
			case SM_Continue:
				if (x == '\0') {
					i++;
					SM_STATE = SM_Lock;
				}
			break;
			
			case SM_Reset:
				if (x == '\0') {
					SM_STATE = SM_Lock;
				}
			break;
				
			case SM_Unlock:
				if ((PINB & 0x80) == 0x00) {
					PORTB = 0x00;
					SM_STATE = SM_Lock;
				}
				else {
					SM_STATE = SM_Unlock;
				}
			break;
				
                        default:
                                SM_STATE = SM_SMStart;
                        break;
}

                switch(SM_STATE) {
                        case SM_SMStart:
                        break;
                        case SM_Lock:
			break;
			case SM_Continue:
			break;
			case SM_Reset:
				PORTB = PORTB & 0xFE;
			break;
			case SM_Unlock:
				PORTB = PORTB | 0x01;
			break;
			
}
}


int main(void) {
	//unsigned char x
    /* Insert DDR and PORT initializations */
	DDRB = 0x03; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	SM_STATE = SM_SMStart;
	K_State = K_Start;
    /* Insert your solution below */
    while (1) {
	 KeypadSM();
	 Tick_Toggle();
	//x = GetKeypadKey();
	/*switch (x) {
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
		*/
    }
    return 1;
}
