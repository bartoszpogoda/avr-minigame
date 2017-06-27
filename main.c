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
#include "gameLogic.h"
#include "graphicsEngine.h"

GameState* gameState;
GraphicsEngine* engine;

int dbg = 0;

ISR(INT0_vect){
	_delay_ms(10);
	onLeftButtonPress(gameState);
}

ISR(INT1_vect){
	_delay_ms(10);
	onRightButtonPress(gameState);
}

int main(void){

	ADCSRA &= ~(1<<ADEN);

	DDRD |= 1<<PD2 | 1<<PD3;
	PORTD |= 1<<PD2 | 1<<PD3;		// Enable PD2 pull-up resistor

	GICR |= 1<<INT0;					// Enable INT0
	MCUCR |= (1<<ISC01 | 1<<ISC00);	// Trigger INT0 on rising edge

	GICR |= 1<<INT1;					// Enable INT1
	MCUCR |= (1<<ISC11 | 1<<ISC10);	// Trigger INT1 on rising edge*/

	DDRB |= 1 << 0;				// enable PORTB.0 for output (repaint blink)
	DDRB |= 1 << 1;				// enable PORTB.1 for output (state change blink)

	sei();				//Enable Global Interrupt

	gameState = malloc(sizeof(GameState));
	engine = malloc(sizeof(GraphicsEngine));


	gInit(engine);
	gameStart(gameState);

	//int counter = 0;
	//int counterRate = 10;

	// repaint loop
	while(1){
		//_delay_ms(300);
		_delay_ms(133);

		gameLoopIteration(gameState);
		// toggle state change blink
		PORTB ^= 1 << 1;

		//if(++counter % counterRate == 0){
			// toggle repaint blink
			PORTB ^= 1 << 0;
			onRedraw(engine, gameState);
		//}

	}
}

