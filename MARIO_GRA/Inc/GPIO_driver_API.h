/*
 * GPIO_driver_API.h
 *
 *  Created on: 2 mar 2026
 *      Author: hasom
 */

#ifndef GPIO_DRIVER_API_H_
#define GPIO_DRIVER_API_H_

#include<"stm32_f411re.h">

typedef struct{

	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPullUpPulldownControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;

typedef struct{

	GPIO_RegDef_t *pGPIO_X_BaseAddr = GPIO_A; //wskaznik na adres bazowy peripherala GPIO- wybieramy sobie ktory chcemy obslugiwac w tej funkcji
	GPIO_PinConfig_t GPIO_PinConfig;


}GPIO_Handle_t;

// to sa api
void GPIO_Init(void); //ustawienie pinu
void GPIO_DeInit(void); //reset pinu
void GPIO_PeripheralClockControl(void); //clock
void GPIO_ReadFromInputPin(void);
void GPIO_ReadFromInputPort(void);
void GPIO_WriteToOutputPin(void);
void GPIO_WrtieToOutputPort(void);
void GPIO_ToggleOutputPin(void);
void GPIO_IRQConfig(void);
void GPIO_IRQHandling(void);




















#endif /* GPIO_DRIVER_API_H_ */
