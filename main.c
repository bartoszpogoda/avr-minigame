/*
 * main.c
 *
 *  Created on: 20.06.2017
 *      Author: Bartosz Pogoda
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	// Hello world blink
	DDRB |= 1 << 0;				// enable PORTB.0 for output
	while(1){
		_delay_ms(1000);
		PORTB ^= 1 << 0;		// toggle PORTB.0
	}
}

