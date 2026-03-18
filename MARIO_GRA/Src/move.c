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

extern uint8_t pos_y0;
extern uint8_t pos_y1;
extern uint8_t button_pressed;





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
/*void move_left(uint32_t move, object *pObject){

	if(move < 1500){
		if(pos_y0 >6){
			pObject->pos_y0	-=5;
			pObject->pos_y1 -=5;
		}
	}
}
*/
void move_jump(uint16_t button){
	button = button_pressed;
	if(!button){
		//if(pos_y1<157){
		//	pos_y1 +=5;
		//}
	}
}
