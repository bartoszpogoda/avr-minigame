/*
 * main.c
 *
 *  Created on: 20.06.2017
 *      Author: Bartosz Pogoda
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "display.h"
#include "graphicsEngine.h"

int it = 0;

ISR(INT0_vect){
	it++;
	if(it > 15){
		it = 0;
	}
}

int main(void){

	DDRD |= (1<<2);
	GICR = 1<<INT0;					// Enable INT0
	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge

	DDRB |= 1 << 0;				// enable PORTB.0 for output (repaint blink)
	DDRB |= 1 << 1;				// enable PORTB.1 for output (state change blink)

	sei();				//Enable Global Interrupt

	GraphicsEngine engine;
	GraphicState state;

	gInit(engine);

	int i=0;
	for(i = 0; i<16 ;i++){
		state.ccodes[i] = 0b01000001;
	}
	for(; i<32 ;i++){
		state.ccodes[i] = 0b00100000;
	}

	int counter = 0;
	int counterRate = 10;

	// repaint loop
	while(1){
		if(++counter % counterRate == 0){
			state.ccodes[it] = state.ccodes[it] + 1;
			// toggle state change blink
			PORTB ^= 1 << 1;

		}
		_delay_ms(50);
		// toggle repaint blink
		PORTB ^= 1 << 0;
		gRepaintDiff(engine,state);
	}
}

