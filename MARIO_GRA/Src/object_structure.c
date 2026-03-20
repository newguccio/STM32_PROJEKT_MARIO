/*
 * object_structure.c
 *
 *  Created on: 18 mar 2026
 *      Author: hasom
 */
#include  <stdint.h>
#include  <stdio.h>
#include "GPIO_driver_API.h"
#include "SPI_Driver_API.h"
#include "object_structure.h"


extern uint8_t gravity;


void SPI_Draw(uint8_t x0, uint8_t x1,uint8_t y0, uint8_t y1, uint16_t color);

void object_draw(object *pObject, uint16_t color){

	pObject->color = color;
	SPI_Draw(pObject->pos_x0,pObject->pos_x1, pObject->pos_y0, pObject->pos_y1, pObject->color);
}













void player_move(object *pObject){






}
