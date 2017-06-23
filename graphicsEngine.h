/*
 * graphicsEngine.h
 *
 *  Created on: 23.06.2017
 *      Author: Student225988
 */

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "pinconfig.h"
#include "display.h"

typedef struct{
	unsigned ccodes[DISPLAY_SIZE];
} GraphicState;

typedef struct{
	GraphicState previousState;
} GraphicsEngine;

void gInit(GraphicsEngine engine);
void gClearPrevState(GraphicsEngine engine);
void gRepaintClear(GraphicsEngine engine, GraphicState state);
void gRepaintDiff(GraphicsEngine engine, GraphicState state);


#endif /* GRAPHICSENGINE_H_ */
