/*
 * display.h
 *
 *  Created on: 20.06.2017
 *      Author: Student225988
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "pinconfig.h"

#define DISPLAY_SIZE 32
#define LED_DISPLAY_SIZE 3

void flashEnable();
void waitBusy();

void sendCommand(unsigned char command);
void sendData(unsigned char data);

// x - column number 	{0,15}
// y - row number 		{0,1}
void setPositionXY(unsigned x, unsigned y);
void setPositionXX(unsigned x);

// sends to id 0 asset
void sendAsset(unsigned pixelLines[7], unsigned id);

void initDisplay();

#endif /* DISPLAY_H_ */
