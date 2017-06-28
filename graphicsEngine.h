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

#define EMPTY_DRAWABLE 0b00100000

typedef unsigned DrawableObject;

// DISPLAY STATES -------------------------
typedef struct{
	DrawableObject drawables[DISPLAY_SIZE];
} DrawableMap;

typedef struct{
	unsigned leds[LED_DISPLAY_SIZE];
} LEDState;
//  ---------------------------------------


// CUSTOM ASSETS --------------------------
typedef struct{
	DrawableObject pixelLines[8];
} Asset;
//  ---------------------------------------


// GRAPHIC ENGINE OBJECT-------------------
typedef struct{
	DrawableMap previousMap;
	DrawableMap	bufferMap;

	LEDState previousLEDState;
	LEDState bufferLEDState;

	Asset* assets;
	unsigned assetsSize;
} GraphicsEngine;
//  ---------------------------------------

// new interface
GraphicsEngine* graphicsEngineInit();

void prepareDraw(GraphicsEngine* engine, DrawableObject, unsigned x, unsigned y);
void prepareDrawString(GraphicsEngine* engine, char* characters, int length, unsigned x, unsigned y);

void prepareLEDDraw(GraphicsEngine* engine, int led);

void executeDraw(GraphicsEngine* engine);
void executeLEDDraw(GraphicsEngine* engine);

void loadAsset(GraphicsEngine*, Asset, DrawableObject);

void clearStateAndBuffers(GraphicsEngine* engine);

#endif /* GRAPHICSENGINE_H_ */
