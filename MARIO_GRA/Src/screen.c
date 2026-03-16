/*
 * screen.c
 *
 *  Created on: 15 mar 2026
 *      Author: hasom
 */


#include  <stdint.h>
#include  <stdio.h>
#include "GPIO_driver_API.h"
#include "SPI_Driver_API.h"



void SPI_Received_Data(SPI_RegDef_t *pSPIx, uint8_t *pRxData, uint32_t length);
void delay_ms(uint32_t ms);




void screen_hardware_reset(void){
	GPIO_C->odr &= ~(1<<0);
	delay_ms(50);
	GPIO_C->odr |= (1<<0);
	delay_ms(50);
}



void command_to_screen(uint8_t command){
//DC = 0 czyli tryb commabd
GPIO_C->odr &= ~(1<<1);

//CS = 0
GPIO_C->odr &= ~(1<<2);
//teraz dziala w trybie otrzymywania rozkazow i dziala bo CS = low

SPI_Data_Send(SPI3, &command , 1);
while(!(SPI3->sr & 1 << 1) );
while( (SPI3->sr & 1 << 7) ); // busy flag czy przetworzym komende

// zeby zachowac kontrole nad stanem ekranu, zebysmy w nastepnej funkcji wiedzieli ze trzeba wlaczyc a nie czy jest wlaczone sie zastanwiac
GPIO_C->odr |= (1<<2);
}


void data_to_screen(uint8_t data){

//DC = 1 czyli tryb data
GPIO_C->odr |= (1<<1);
//CS = 0
GPIO_C->odr &= ~(1<<2);
//teraz dziala w trybie otrzymywania rozkazow i dziala bo CS = low
SPI_Data_Send(SPI3, &data, 1);
while(!(SPI3->sr & 1 << 1) );
while( (SPI3->sr & (1 << 7)) );


GPIO_C->odr |= (1 << 2);
}


//x0 start_x, x1 end_x     y0 start_y, y1 end_y			zakres 0-127 (X) i 0-159 (Y)
void SPI_Set_Cursor(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1){

	 command_to_screen(0x2A);
	 data_to_screen(0);
	 data_to_screen(x0);
	 data_to_screen(0);
	 data_to_screen(x1);

	 command_to_screen(0x2B);
	 data_to_screen(0);
	 data_to_screen(y0);
	 data_to_screen(0);
	 data_to_screen(y1);


}


void SPI_Draw(uint8_t x0, uint8_t x1,uint8_t y0, uint8_t y1, uint16_t color){

	//memory write

	SPI_Set_Cursor(x0, x1, y0,y1);
	command_to_screen(0x2C);

	uint32_t obszar = (x1-x0+1)*(y1-y0+1);

	for(uint32_t i =0; i < obszar;i++){
		data_to_screen(color >> 8);   // Bajt 1
		data_to_screen(color & 0xFF);
	}




}
