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


void command_to_screen(uint8_t command){
//DC = 0 czyli tryb commabd
GPIO_C->odr &= ~(1<<1);

//CS = 0
GPIO_C->odr &= ~(1<<2);
//teraz dziala w trybie otrzymywania rozkazow i dziala bo CS = low

SPI_Data_Send(SPI3, &command , 1);

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

while( (SPI3->sr & (1 << 7)) );

GPIO_C->odr |= (1 << 2);
}



void SPI_Set_Cursor(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){

	// 1. Ustawienie zakresu KOLUMN (X)
	    command_to_screen(0x2A);
	    data_to_screen(0x00); // High byte (zawsze 0 dla 128px)
	    data_to_screen(x0);   // Start X
	    data_to_screen(0x00); // High byte
	    data_to_screen(x1);   // Koniec X

	    // 2. Ustawienie zakresu WIERSZY (Y)
	    command_to_screen(0x2B);
	    data_to_screen(0x00); // High byte
	    data_to_screen(y0);   // Start Y
	    data_to_screen(0x00); // High byte
	    data_to_screen(y1);   // Koniec Y

	    // 3. Rozkaz zapisu do pamięci (RAM WRITE)
	    // Wszystko co wyślesz po tej komendzie, ekran uzna za kolory pikseli
	    command_to_screen(0x2C);




}


void SPI_Draw(uint8_t x, uint8_t y, uint16_t color){

	if(x >= 128 || y >= 160) return;

	    // Ustawiamy okno 1x1 w punkcie (x, y)
	SPI_Set_Cursor(x, y, x, y);

	    // Wysyłamy 16-bitowy kolor jako dwa bajty (bo DFF=8)
	    data_to_screen(color >> 8);   // Starszy bajt (np. 0xF8)
	    data_to_screen(color & 0xFF); // Młodszy bajt (np. 0x00)


}
