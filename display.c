/*
 * display.c
 *
 *  Created on: 20.06.2017
 *      Author: Student225988
 */
#include "display.h"
#include <avr/io.h>
#include <util/delay.h>

void flashEnable(){
	D_CONTROL_PORT |= 1<< D_ENABLE;
	asm volatile ("nop");
	asm volatile ("nop");
	D_CONTROL_PORT &= ~1<<D_ENABLE;
}

void waitBusy(){
	D_DATA_DIR = 0;

	D_CONTROL_PORT |= (1 << D_RW);
	D_CONTROL_PORT &= ~(1 << D_RS);

	while(D_DATA_PORT > 0b1000000){
		flashEnable();
	}

	D_DATA_DIR = 0xFF;
}

void sendCommand(unsigned char command){
	waitBusy();
	D_DATA_PORT = command;

	D_CONTROL_PORT &= ~(1<<D_RW);
	D_CONTROL_PORT &= ~(1<<D_RS);
	flashEnable();

	D_DATA_PORT = 0;
}

void sendData(unsigned char data){
	waitBusy();
	D_DATA_PORT = data;

	D_CONTROL_PORT &= ~(1<<D_RW);
	D_CONTROL_PORT |= (1<<D_RS);
	flashEnable();

	D_DATA_PORT = 0;
}

void setPositionXY(unsigned x, unsigned y){
	sendCommand((0b10000000 | x) + (y ? 0x40 : 0));
}

void setPositionXX(unsigned x){
	if(x>15){
		setPositionXY(x%16, 1);
	} else{
		setPositionXY(x, 0);
	}
}

void initDisplay(){
	D_CONTROL_DIR |= 1 << D_ENABLE | 1 << D_RW | 1 << D_RS;
	D_CONTROL_PORT &= ~(1 << D_ENABLE | 1 << D_RW | 1 << D_RS);
	D_DATA_DIR = 0xFF;

	_delay_ms(20);
	sendCommand(0x01);
	_delay_ms(2);
	sendCommand(0x38);
	_delay_ms(50);
	sendCommand(0b00001100);
	_delay_ms(50);
}

void sendAsset(unsigned pixelLines[8], unsigned id){
	sendCommand(0b01000000 + id*8);
	_delay_ms(5);
	int i = 0;
	for( ; i < 8 ; i++){
		sendData(pixelLines[i]);
	}
}

