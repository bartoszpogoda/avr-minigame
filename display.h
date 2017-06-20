/*
 * display.h
 *
 *  Created on: 20.06.2017
 *      Author: Student225988
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "pinconfig.h"

void flashEnable();
void waitBusy();

void sendCommand(unsigned char command);
void sendData(unsigned char data);

void initDisplay();


#endif /* DISPLAY_H_ */
