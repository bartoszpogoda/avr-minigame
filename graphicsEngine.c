/*
 * graphicsEngine.c
 *
 *  Created on: 23.06.2017
 *      Author: Student225988
 */

#include "graphicsEngine.h"
#include "display.h"
#include <avr/delay.h>

void gInit(GraphicsEngine engine){
	gClearPrevState(engine);
	initDisplay();
}

void gClearPrevState(GraphicsEngine engine){
	unsigned i = 0;
	while(i ^ DISPLAY_SIZE){
		engine.previousState.ccodes[i] = 0b00100000;	//empty character
		i++;
	}
}

void gRepaintClear(GraphicsEngine engine, GraphicState state){
	sendCommand(0x01); // clear
	_delay_ms(5);
	setPositionXY(0,0);
	int i = 0;
	while(i ^ 16){
		sendData(state.ccodes[i]);
		engine.previousState.ccodes[i] = state.ccodes[i];
		i++;
	}
	setPositionXY(0,1);

	i = 15;
	while(i ^ 32){
		sendData(state.ccodes[i]);
		engine.previousState.ccodes[i] = state.ccodes[i];
		i++;
	}
}

void gRepaintDiff(GraphicsEngine engine, GraphicState state){
	_delay_ms(5);
	int i = 0;
	while(i ^ 32){
		if(engine.previousState.ccodes[i] != state.ccodes[i]){
			setPositionXX(i);
			sendData(state.ccodes[i]);
		}
		engine.previousState.ccodes[i] = state.ccodes[i];
		i++;
	}
}
