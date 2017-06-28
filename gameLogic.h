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

typedef struct{
	DrawableObject doPlayerStanding;
	DrawableObject doPlayerJumping;
	DrawableObject doBarrelAnim0;
	DrawableObject doBarrelAnim1;

	int anGlobalCounter;

	int anBarrelFrame;
	int anBarrelFreq;

	unsigned playerPosition;
	unsigned playerHealth;
	unsigned playerJumptimeout;
	unsigned barrelPosition;
	int gameOverFlag;
} GameState;

void gameStart(GameState* gs);

void gameInitGraphics(GameState* gs, GraphicsEngine* gEngine);

void gameLoopIteration(GameState* gs);

void onLeftButtonPress(GameState* gs);

void onRightButtonPress(GameState* gs);

void onRedraw(GraphicsEngine* engine, GameState* gs);

#endif /* GAMELOGIC_H_ */
