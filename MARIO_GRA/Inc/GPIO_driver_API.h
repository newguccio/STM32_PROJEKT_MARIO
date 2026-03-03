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
void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOX, uint8_t EnableOrDisable); //clock



void GPIO_Init(GPIO_Handle_t *pGPIOHandle); //ustawienie/inicjalizacja pinu zeby zaczal dzialac
void GPIO_DeInit(GPIO_RegDef_t *pGPIOX); //reset pinu co byl init, poprzez wejscie do rcc pheripheral reset register

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOX);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber, uint8_t value);
void GPIO_WrtieToOutputPort(GPIO_RegDef_t *pGPIOX, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber);



void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnodDi); //enodi-enable or disable
void GPIO_IRQHandling(uint8_t PinNumber);















#endif /* GPIO_DRIVER_API_H_ */
