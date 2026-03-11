/*
 * SPI_Driver_API.c
 *
 *  Created on: 10 mar 2026
 *      Author: hasom
 */
#include "SPI_Driver_API.h"



void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIOx, uint8_t EnableOrDisable){
	if(EnableOrDisable ==1){
		if(pSPIOx == SPI1){
			APB2_SPI1_Enable();
		}
		else if(pSPIOx == SPI2){
			APB1_SPI2_Enable();
		}
		else if(pSPIOx == SPI3){
			APB1_SPI3_Enable();
		}
	}
	else{
		if(pSPIOx == SPI1){
		RCC->apb2enr.spi1en |= 0; // nie chce mi sie robic makra na wyłączanie
		}
		else if(pSPIOx == SPI2){
		RCC->apb1enr.spi2en |= 0;
		}
		else if(pSPIOx == SPI3){
		RCC->apb1enr.spi3en |= 0;
		}
	}
}


void SPI_Init(SPI_Handle_t *pSPIHandle){

	uint32_t temp = 0;
	//device mode
	temp |= pSPIHandle->SPI_Config.SPI_DeviceMode << 2 ; //robimy sobie taki przejsciowy pusty rejestr i w jego odpowiednie miejsca wpisujemy sobie co chcemy tworzac lustrzane odbicie dla nrazie CR1 bo potem tam to przypiszemy.
	//bus config
	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BusConfig_fullduplex){
	//	pSPIHandle->pSPIx->cr1 &= ~(1<<15); //tak lepiej nie robic, bo niepotrzbnie co chwile dostajemy sie do rzeczywistego rejestru
		temp &= ~(1<<15); 			//bidimode na 0 upewniamy sie bo 0 jest domyslnie

	}else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BusConfig_halfduplex){
		temp|= (1<<15);					//bidimode na 1 bo 1-line bidirectional

	}else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BusConfig_simplex_rxonly){
		temp &= ~(1<<15);				//bidimode na 0 upewniamy sie bo 0 jest domyslnie i usawiamy RXonly na 1
		temp |=  (1<<10);
	}
	temp |= pSPIHandle->SPI_Config.SPI_CPHA << 0;
	temp |= pSPIHandle->SPI_Config.SPI_CPOL << 1;
	temp |= pSPIHandle->SPI_Config.SPI_SclkSpeed << 3;
	temp |= pSPIHandle->SPI_Config.SPI_SSM << 9;
	temp |= pSPIHandle->SPI_Config.SPI_DFF << 11;

	pSPIHandle->pSPIx->cr1 = temp;  //lepiej dac samo = bo na poczatku ustalilismy ze temp=0, a CR1 nie wiemy czy napewno są same 0
}
void SPI_DeInit(SPI_RegDef_t *pSPIx);

//blocking base- non interrupt
void SPI_Data_Send(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t length){

	while(length >0){

		while (!( pSPIx->sr & (1 << 1) )); //patrzymy flage txe czy nie jest 0, zadzialaloba zwykla ekstrakcja pSPIx->sr >> 1 & 1, ale uzyty zapis sprawdza czy w 1 pozycji jest 1 a nie spisuje jego wartosc
	//	while(SPI_GetStatusFlag(pSPIx, SPI_TXE_Flag)== Flag_Reset); to samo co na gorze ale w funkcji wiec mozna w niej sprawdza rozne flagi nie tylko ta jedna
		if( ( pSPIx->cr1 & (1 << 11 ) ) ){ // jesli  jest tam cokolwiek to data format == 16, nie mozemy sprawdzi ==1 to bo tajkbysmy porownywali cala liczbe do 1 a chcemy tylko pozycje, == (1 <<11) by zadzialalo
			pSPIx->dr = *((uint16_t*)pTxBuffer); //ładujemy dane do buforu,a typecastujemy bo dalismy uint8 a dla 16bitow chcemu uint16
			length--; //dwa razy bo 16 bitow chcemy a wysyla sie po 8 wiec dwa walimy
			length--;
			(uint16_t*)pTxBuffer++; //inkrementujemy po tym jak odbjerzemy bajt cały
		}else {
			pSPIx->dr = *pTxBuffer;
			length--;
			pTxBuffer++;
		}
	}





}
void SPI_Received_Data(SPI_RegDef_t *pSPIx, uint8_t *pRxData, uint32_t length);

void SPI_IRinterruptQConfig(uint8_t IRQNumber, uint8_t EnodDi);
void SPI_PriorityConfig(uint8_t Priority, uint8_t IRQNumber);
void SPI_IRQHandling(SPI_Handle_t *pHandle);




//funkcja do patrzenia jaka jest flaga- jebac to
uint8_t SPI_GetStatusFlag(SPI_RegDef_t *pSPIx, uint32_t FlagName){

	if(pSPIx->sr & FlagName){
		return Flag_Set;
	}
	return Flag_Reset;
}




















