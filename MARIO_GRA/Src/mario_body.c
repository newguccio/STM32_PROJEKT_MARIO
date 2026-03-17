/*
 * mario_body.c
 *
 *  Created on: Mar 17, 2026
 *      Author: gustaw
 */

#include  <stdint.h>
#include  <stdio.h>
#include "GPIO_driver_API.h"
#include "SPI_Driver_API.h"


void SPI_Draw(uint8_t x0, uint8_t x1,uint8_t y0, uint8_t y1, uint16_t color);


uint32_t body(uint8_t x0, uint8_t x1,uint8_t y0, uint8_t y1, uint16_t color){


	SPI_Draw();

}

