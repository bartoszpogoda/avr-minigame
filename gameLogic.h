/*
 * gameEngine.h
 *
 *  Created on: 26.06.2017
 *      Author: Student225988
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "graphicsEngine.h"

#define JUMP_TIMEOUT 4
#define BARREL_SPAWN_PROB 30

typedef struct{
	int barrelPosition;
	int barrelDirection;
	int anBarrelFrame;
	int inGame;
} Barrel;

typedef struct{
	DrawableObject doPlayerStanding;
	DrawableObject doPlayerJumping;
	DrawableObject doBarrelAnim0;
	DrawableObject doBarrelAnim1;

	int anGlobalCounter;
	int anBarrelFreq;

	unsigned playerInAirFlag;
	unsigned playerPosition;
	unsigned playerHealth;
	unsigned playerJumptimeout;

	Barrel barrels[2];
	int barrelsSize;

	int gameOverFlag;
} GameState;

void gameStart(GameState* gs);

void gameInitGraphics(GameState* gs, GraphicsEngine* gEngine);

void gameLoopIteration(GameState* gs);

void onLeftButtonPress(GameState* gs);

void onRightButtonPress(GameState* gs);

void onRedraw(GraphicsEngine* engine, GameState* gs);

#endif /* GAMELOGIC_H_ */
