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
#include "object_structure.h"

void delay_ms(uint32_t ms);
extern uint8_t button_pressed;
extern uint8_t gravity;



void move(uint32_t move, object *pObject){
	if(move > 2500){
		if(pObject->pos_y1 < 154){
		pObject->pos_y1 +=5;
		pObject->pos_y0 +=5;
		}
	}
	if(move < 1500){
		if(pObject->pos_y0 >6){
			pObject->pos_y0	-=5;
			pObject->pos_y1 -=5;
		}
	}
}


void move_jump(uint8_t button, object *pObject){
	button = button_pressed;
	if(!button){
		pObject->speed = -5;
		if(pObject->pos_x1 < 89 ){
		pObject->pos_x0 +=40;
		pObject->pos_x1 +=40;
		}
	}
}

uint8_t check_colisilon(object *pPlayer, object *pObject){

	uint8_t colision = 0;
	if(pObject->pos_x1 > pPlayer->pos_x1 && pObject->pos_x0 > pPlayer->pos_x0){
		colision = 1;
	}

}

