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



void move_right(uint16_t move){

	if(move > 2500){

	//117 bo 128 to granica wiec do 131max mozne sie jeszcze poruszyc
	if(pos_x < 117 && pos_x>0){
	pos_x +=2;
}else{
	pos_x = pos_x;
}


	}
}
