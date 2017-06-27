/*
 * graphicsEngine.c
 *
 *  Created on: 23.06.2017
 *      Author: Student225988
 */

#include "graphicsEngine.h"
#include "display.h"
#include <avr/delay.h>
#include <avr/io.h>

void gInit(GraphicsEngine* engine){
	//init LED
	LED_DIR |= (1<<LED_0 | 1<<LED_1 | 1<<LED_2);

	gClearPrevState(engine);
	initDisplay();
}

void gClearPrevState(GraphicsEngine* engine){
	unsigned i = 0;
	while(i ^ DISPLAY_SIZE){
		engine->previousState.ccodes[i] = 0b00100000;	//empty character
		i++;
	}

	i=0;
	while(i ^ LED_DISPLAY_SIZE){
		engine->previousLEDState.leds[i] = 0;
		i++;
	}
}

void gRepaintClear(GraphicsEngine* engine, GraphicState state){
	sendCommand(0x01); // clear
	_delay_ms(5);
	setPositionXY(0,0);
	int i = 0;
	while(i ^ 16){
		sendData(state.ccodes[i]);
		engine->previousState.ccodes[i] = state.ccodes[i];
		i++;
	}
	setPositionXY(0,1);

	i = 15;
	while(i ^ 32){
		sendData(state.ccodes[i]);
		engine->previousState.ccodes[i] = state.ccodes[i];
		i++;
	}
}

void gRepaintDiff(GraphicsEngine* engine, GraphicState state){
	_delay_ms(5);
	int i = 0;
	while(i ^ 32){
		if(engine->previousState.ccodes[i] != state.ccodes[i]){
			setPositionXX(i);
			sendData(state.ccodes[i]);
		}
		engine->previousState.ccodes[i] = state.ccodes[i];
		i++;
	}
}


GraphicState gGetClearState(){
	GraphicState state;
	unsigned i = 0;
	while(i ^ DISPLAY_SIZE){
		state.ccodes[i] = 0b00100000;	//empty character
		i++;
	}
	return state;
}

LedDisplayState gGetClearLEDState(){
	LedDisplayState state;
	unsigned i = 0;
	while(i ^ LED_DISPLAY_SIZE){
		state.leds[i] = 0;
		i++;
	}
	return state;
}


void gRepaintLED(GraphicsEngine* engine, LedDisplayState state){
	unsigned i = 0;
	while(i ^ LED_DISPLAY_SIZE){
		if(state.leds[i] != engine->previousLEDState.leds[i]){
			switch(i){
				case 0:
					LED_PORT ^= 1 << LED_0;
					break;
				case 1:
					LED_PORT ^= 1 << LED_1;
					break;
				case 2:
					LED_PORT ^= 1 << LED_2;
					break;
			}
			engine->previousLEDState.leds[i] = state.leds[i];
		}
		i++;
	}
}
