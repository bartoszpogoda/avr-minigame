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
	gs->barrelsSize = 2;
	int i;
	for(i=0;i<gs->barrelsSize;i++){
		gs->barrels[i].barrelPosition = -30;
		gs->barrels[i].barrelDirection = 0;
		gs->barrels[i].anBarrelFrame = 0;
		gs->barrels[i].inGame = 0;
	}

	gs->playerInAirFlag = 0;	// on ground
	gs->playerPosition = 7;	// left side of range in the middle 7-8
	gs->playerJumptimeout = 0;
	gs->gameOverFlag = 0;
	gs->playerHealth = 3;


	gs->anGlobalCounter = 0;
	gs->anBarrelFreq = 2;

	srand(1234);
}

void gameInitGraphics(GameState* gs, GraphicsEngine* gEngine){

	gs->doPlayerStanding = 0;
	Asset assPlayerStanding;
	assPlayerStanding.pixelLines[0] = 0b00000;
	assPlayerStanding.pixelLines[1] = 0b00100;
	assPlayerStanding.pixelLines[2] = 0b00000;
	assPlayerStanding.pixelLines[3] = 0b11111;
	assPlayerStanding.pixelLines[4] = 0b11011;
	assPlayerStanding.pixelLines[5] = 0b10101;
	assPlayerStanding.pixelLines[6] = 0b01010;
	assPlayerStanding.pixelLines[7] = 0b01010;
	loadAsset(gEngine, assPlayerStanding, gs->doPlayerStanding);

	gs->doPlayerJumping = 1;
	Asset assPlayerJumping;
	assPlayerJumping.pixelLines[0] = 0b00100;
	assPlayerJumping.pixelLines[1] = 0b00000;
	assPlayerJumping.pixelLines[2] = 0b11111;
	assPlayerJumping.pixelLines[3] = 0b11011;
	assPlayerJumping.pixelLines[4] = 0b10101;
	assPlayerJumping.pixelLines[5] = 0b01010;
	assPlayerJumping.pixelLines[6] = 0b00000;
	assPlayerJumping.pixelLines[7] = 0b00000;
	loadAsset(gEngine, assPlayerJumping, gs->doPlayerJumping);

	gs->doBarrelAnim0 = 2;
	Asset assBarrelAnim0;
	assBarrelAnim0.pixelLines[0] = 0b00000;
	assBarrelAnim0.pixelLines[1] = 0b00000;
	assBarrelAnim0.pixelLines[2] = 0b00000;
	assBarrelAnim0.pixelLines[3] = 0b00000;
	assBarrelAnim0.pixelLines[4] = 0b00110;
	assBarrelAnim0.pixelLines[5] = 0b01111;
	assBarrelAnim0.pixelLines[6] = 0b01111;
	assBarrelAnim0.pixelLines[7] = 0b00110;
	loadAsset(gEngine, assBarrelAnim0, gs->doBarrelAnim0);

	gs->doBarrelAnim1 = 3;
	Asset doBarrelAnim1;
	doBarrelAnim1.pixelLines[0] = 0b00000;
	doBarrelAnim1.pixelLines[1] = 0b00000;
	doBarrelAnim1.pixelLines[2] = 0b00000;
	doBarrelAnim1.pixelLines[3] = 0b00110;
	doBarrelAnim1.pixelLines[4] = 0b01111;
	doBarrelAnim1.pixelLines[5] = 0b01111;
	doBarrelAnim1.pixelLines[6] = 0b00110;
	doBarrelAnim1.pixelLines[7] = 0b00000;
	loadAsset(gEngine, doBarrelAnim1, gs->doBarrelAnim1);

}

void gameLoopIteration(GameState* gs){
	// game over logic
	if(gs->gameOverFlag) return;

	// player movement (jump logic)
	if(gs->playerJumptimeout > 0){
		gs->playerJumptimeout--;

		if(gs->playerJumptimeout == 0){
			gs->playerInAirFlag = 0;
		}
	}

	// barrels routines
	int i;
	for(i=0;i<gs->barrelsSize && gs->barrels[i].inGame;i++){
		if(gs->barrels[i].inGame == 0) continue;
		// barrel movement
		gs->barrels[i].barrelPosition += gs->barrels[i].barrelDirection;

		// player hit
		if(gs->playerInAirFlag == 0 && gs->playerPosition == gs->barrels[i].barrelPosition){
			gs->playerHealth--;
			if(gs->playerHealth == 0){
				gs->gameOverFlag = 1;
			}
		}

		// out of map check
		if(gs->barrels[i].barrelPosition < 0 || gs->barrels[i].barrelPosition > 15){
				gs->barrels[i].inGame = 0;
		}
	}

	// barrel spawning
	for(i=0;i<gs->barrelsSize;i++){
		if(gs->barrels[i].inGame == 1) continue;
		if(rand() % 100 < BARREL_SPAWN_PROB){
			gs->barrels[i].barrelDirection = rand() % 2 ? 1 : -1;
			gs->barrels[i].barrelPosition = gs->barrels[i].barrelDirection == 1 ? 0 : 15;
			gs->barrels[i].inGame = 1;
		}
	}

}

void onLeftButtonPress(GameState* gs){
	if(gs->playerJumptimeout == 0){
		gs->playerJumptimeout = JUMP_TIMEOUT;
		gs->playerInAirFlag = 1;
	}
}

void onRightButtonPress(GameState* gs){
	gs->playerPosition = gs->playerPosition == 7 ? 8 : 7;
}

void onRedraw(GraphicsEngine* gEngine, GameState* gs){

	if(gs->gameOverFlag){
		char* gameOverString = "Game over";
		char* gameOverString1 = "You noob...";

		prepareDrawString(gEngine, gameOverString, 9, 0,0);
		prepareDrawString(gEngine, gameOverString1, 11, 3,1);

	} else{
		gs->anGlobalCounter++;

		// draw player
		if(gs->playerInAirFlag == 0)
			prepareDraw(gEngine,gs->doPlayerStanding,gs->playerPosition,1);
		else
			prepareDraw(gEngine,gs->doPlayerJumping,gs->playerPosition,0);


		// draw barrel
		int i;
		for(i=0;i<gs->barrelsSize && gs->barrels[i].inGame;i++){
			if(gs->anGlobalCounter % gs->anBarrelFreq == 0){
				gs->barrels[i].anBarrelFrame = (gs->barrels[i].anBarrelFrame ? 0 : 1);
			}
			if(gs->barrels[i].anBarrelFrame == 0){
				prepareDraw(gEngine,gs->doBarrelAnim0,gs->barrels[i].barrelPosition,1);
			} else{
				prepareDraw(gEngine,gs->doBarrelAnim1,gs->barrels[i].barrelPosition,1);
			}
		}

	}

	executeDraw(gEngine);

	// draw health
	int healthIterator = 0;
	while(healthIterator < gs->playerHealth){
		prepareLEDDraw(gEngine, healthIterator);
		healthIterator++;
	}

	executeLEDDraw(gEngine);
}


