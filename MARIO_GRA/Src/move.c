/*
 * move.c
 *
 *  Created on: Mar 17, 2026
 *      Author: gustaw
 */


#include  <stdint.h>
#include  <stdio.h>
#include "GPIO_driver_API.h"
#include "SPI_Driver_API.h"

extern uint8_t pos_y0;
extern uint8_t pos_y1;
extern uint8_t button_pressed;
void move_right(uint32_t move){

	if(move > 2500){

	//117 bo 128 to granica wiec do 131max mozne sie jeszcze poruszyc
	if(pos_y1 < 144){
	pos_y1 +=2;
	pos_y0 +=2;
}

		}
}
void move_left(uint32_t move){

	if(move < 1500){
		if(pos_y0 >3){
			pos_y0 -=2;
			pos_y1 -=2;
		}
	}
}
void move_jump(uint16_t button){
	button = button_pressed;
	if(!button){
		//if(pos_y1<157){
		//	pos_y1 +=5;
		//}
	}
}
