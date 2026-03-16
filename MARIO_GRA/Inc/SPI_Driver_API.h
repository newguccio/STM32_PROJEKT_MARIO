/*
 * SPI_Driver_API.h
 *
 *  Created on: 10 mar 2026
 *      Author: hasom
 */

#ifndef SPI_DRIVER_API_H_
#define SPI_DRIVER_API_H_

#include"stm32_f411re.h"



//master produces clock- trzeba pamietac
//nalezy sprawdzic u producenta jakie cpol i cpha ustawic
//trzeba sprawdzic piny jakie sa i sprawdzi czy dupleks/halfdupleks/simpleks i w zaleznosci od tego inne rejestry beda wymagaly korekty



//device mode macros
#define SPI_Master 							1
#define SPI_Slave 							0

#define SPI_BusConfig_fullduplex			1 //zazwyczaj ten
#define SPI_BusConfig_halfduplex			2
#define SPI_BusConfig_simplex_rxonly		3

//speed control jest w CR1 pod BR (baud rate)
#define SPI_SCLK_SPEED_div2					0
#define SPI_SCLK_SPEED_div4	 				1
#define SPI_SCLK_SPEED_div8					2
#define SPI_SCLK_SPEED_div16				3
#define SPI_SCLK_SPEED_div32				4 // jest heszcze 64,128 i 256


//data frame format- ile bitow na ramke transmisji
#define SPI_dff_8bits						0
#define SPI_dff_16bits						1

//clock polarity
#define SPI_CPOL_0							0
#define SPI_CPOL_1							1

//clock phase
#define SPI_CPHA_0							0
#define SPI_CPHA_1							1

#define SPI_SSM_hardware					0
#define SPI_SSM_software					1 //domyslnie jest hardwere wiec bit w ssm musi byc 1



#define Flag_Set 							1
#define Flag_Reset							0

#define SPI_SR_TXE							1					//bit position w rejestrze cr, jak chcemy inne flagi sprawdza w funkcji to trzeba dodac pozostale makra jak to
#define SPI_TXE_Flag						(1 << SPI_SR_TXE)

//w rejestrze cr1 jesli uzywamy halfpuplex trzeba ustawic BidiMode na 1 i kontrolowac zmieniac Bidioe i wsm sporo innych


#define Sleep_Out 			0x11
#define Display_On 			0x29


typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_Config_T;

typedef struct{

	SPI_RegDef_t *pSPIx;
	SPI_Config_T SPI_Config;

}SPI_Handle_t;


void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIOx, uint8_t EnableOrDisable);

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

//blocking base- non interrupt
void SPI_Data_Send(SPI_RegDef_t *pSPIx, uint8_t *pTxData, uint32_t length);
void SPI_Received_Data(SPI_RegDef_t *pSPIx, uint8_t *pRxData, uint32_t length);

void SPI_IRinterruptQConfig(uint8_t IRQNumber, uint8_t EnodDi);
void SPI_PriorityConfig(uint8_t Priority, uint8_t IRQNumber);
void SPI_IRQHandling(SPI_Handle_t *pHandle);










#endif /* SPI_DRIVER_API_H_ */
