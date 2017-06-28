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
#include <stdlib.h>

GraphicsEngine* graphicsEngineInit(){
	//LED INIT
	LED_DIR |= (1<<LED_0 | 1<<LED_1 | 1<<LED_2);

	//LCD INIT
	initDisplay();

	//INIT ENGINE
	GraphicsEngine* engine = malloc(sizeof(GraphicsEngine));
	engine->assetsSize = 0;
	clearStateAndBuffers(engine);
	return engine;
}

void prepareDraw(GraphicsEngine* engine, DrawableObject drawable, unsigned x, unsigned y){
	engine->bufferMap.drawables[x + 16*y] = drawable;
}
void prepareDrawString(GraphicsEngine* engine, char* characters, int length, unsigned x, unsigned y){
	int i = 0;
	int curr_x = x;
	int curr_y = y;
	while(i ^ length){
		prepareDraw(engine, characters[i], curr_x, curr_y);

		curr_x++;
		if(curr_x>15){
			curr_x = 0;
			curr_y++;
		}
		i++;
	}
}

void prepareLEDDraw(GraphicsEngine* engine, int led){
	engine->bufferLEDState.leds[led] = 1;
}

void executeDraw(GraphicsEngine* engine){
	_delay_ms(5);
	int i = 0;
	while(i ^ 32){
		if(engine->previousMap.drawables[i] != engine->bufferMap.drawables[i]){
			setPositionXX(i);
			sendData(engine->bufferMap.drawables[i]);
		}
		engine->previousMap.drawables[i] = engine->bufferMap.drawables[i];
		engine->bufferMap.drawables[i] = EMPTY_DRAWABLE;
		i++;
	}
}

void executeLEDDraw(GraphicsEngine* engine){
	unsigned i = 0;
	while(i ^ LED_DISPLAY_SIZE){
		if(engine->bufferLEDState.leds[i] != engine->previousLEDState.leds[i]){
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
		}
		engine->previousLEDState.leds[i] = engine->bufferLEDState.leds[i];
		engine->bufferLEDState.leds[i] = 0;	//clr buffer
		i++;
	}
}

//TODO implement
void loadAsset(GraphicsEngine* engine, Asset asset, DrawableObject id){
	sendAsset(asset.pixelLines, id);
}

void clearStateAndBuffers(GraphicsEngine* engine){
	unsigned i = 0;
	while(i ^ DISPLAY_SIZE){
		engine->previousMap.drawables[i] = EMPTY_DRAWABLE;
		engine->bufferMap.drawables[i] = EMPTY_DRAWABLE;
		i++;
	}

	i=0;
	while(i ^ LED_DISPLAY_SIZE){
		engine->previousLEDState.leds[i] = 0;
		engine->bufferLEDState.leds[i] = 0;
		i++;
	}
}

