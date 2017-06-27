/*
 * gameLogic.c
 *
 *  Created on: 26.06.2017
 *      Author: Student225988
 */

#include "gameLogic.h"
#include "avr/io.h"
#include <stdlib.h>

void gameStart(GameState* gs){
	if(rand() % 2){
		gs->barrelPosition = 15;
	} else{
		gs->barrelPosition = 31;
	}

	gs->playerPosition = 16;	// on ground
	gs->playerJumptimeout = 0;
	gs->gameOverFlag = 0;
	gs->playerHealth = 3;

	srand(1234);
}

void gameLoopIteration(GameState* gs){
	// game over logic
	if(gs->gameOverFlag) return;

	// player movement (jump logic)
	if(gs->playerJumptimeout > 0){
		gs->playerJumptimeout--;

		if(gs->playerJumptimeout == 0){
			gs->playerPosition = 16;
		}
	}

	// barrel movement
	gs->barrelPosition--;
	// player hit
	if(gs->playerPosition == gs->barrelPosition){
		gs->playerHealth--;
		if(gs->playerHealth == 0){
			gs->gameOverFlag = 1;
		}
	}

	if(gs->barrelPosition == 15 || gs->barrelPosition == -1){
		if(rand() % 2){	//restart barrel
			gs->barrelPosition = 15;
		} else{
			gs->barrelPosition = 31;
		}
	}
}

void onLeftButtonPress(GameState* gs){
	if(gs->playerJumptimeout == 0){
		gs->playerJumptimeout = JUMP_TIMEOUT;
		gs->playerPosition = 0;
	}
}

void onRightButtonPress(GameState* gs){
	//NOP
}

void onRedraw(GraphicsEngine* gEngine, GameState* gs){

	GraphicState state = gGetClearState();

	if(gs->gameOverFlag){
		state.ccodes[0] = 'G';
		state.ccodes[1] = 'O';
		state.ccodes[2] = '!';

	} else{
		// draw player
		if(gs->playerPosition == 16)
			state.ccodes[16] = 'X';
		else
			state.ccodes[0] = 'X';

		// draw barrel
		int i;
		for(i = 0; i<32 ;i++){
			if(gs->barrelPosition == i)
				state.ccodes[i] = 'O';
		}
	}

	gRepaintDiff(gEngine,state);

	// draw health
	LedDisplayState healthDisplay = gGetClearLEDState();
	int healthIterator = 0;
	while(healthIterator < gs->playerHealth){
		healthDisplay.leds[healthIterator] = 1;
		healthIterator++;
	}

	gRepaintLED(gEngine, healthDisplay);
}


