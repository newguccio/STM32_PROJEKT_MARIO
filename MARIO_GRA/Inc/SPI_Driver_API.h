/*
 * SPI_Driver_API.h
 *
 *  Created on: 10 mar 2026
 *      Author: hasom
 */

#ifndef SPI_DRIVER_API_H_
#define SPI_DRIVER_API_H_



typedef struct{
	uint8_t SPI_DevieMode;
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





#endif /* SPI_DRIVER_API_H_ */
