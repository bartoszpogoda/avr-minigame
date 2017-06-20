/*
 * main.c
 *
 *  Created on: 20.06.2017
 *      Author: Bartosz Pogoda
 */

#include <avr/io.h>
#include <util/delay.h>

#include "display.h"

int main(void){
	// Hello world LCD
	initDisplay();
	char helloWorld[5] = {'h','e','l','l','o'};
	int i = 0;
	while(i<5){
		sendData(helloWorld[i]);
		i++;
	}

	// Hello world blink
	DDRB |= 1 << 0;				// enable PORTB.0 for output
	while(1){
		_delay_ms(1000);
		PORTB ^= 1 << 0;		// toggle PORTB.0
	}
}

