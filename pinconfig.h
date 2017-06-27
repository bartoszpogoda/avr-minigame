/*
 * pinconfig.h
 *
 *  Created on: 20.06.2017
 *      Author: Student225988
 */

#ifndef PINCONFIG_H_
#define PINCONFIG_H_

// LED display config
#define LED_DIR DDRA
#define LED_PORT PORTA
#define LED_0	PA0
#define LED_1	PA1
#define LED_2	PA2

// LCD display config
#define D_CONTROL_PORT 	PORTD
#define D_CONTROL_DIR	DDRD
#define D_ENABLE PD4
#define D_RW PD5
#define D_RS PD6

#define D_DATA_PORT PORTC
#define D_DATA_DIR	DDRC

#endif /* PINCONFIG_H_ */
