/*
 * GPIO_driver_API.h
 *
 *  Created on: 2 mar 2026
 *      Author: hasom
 */

#ifndef GPIO_DRIVER_API_H_
#define GPIO_DRIVER_API_H_

#include"stm32_f411re.h"


// STRUKTURY POD GPIO API
typedef struct{

	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPullUpPulldownControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;					//to dziala tylko kesli Pinmoder ustawiny na alternate function

}GPIO_PinConfig_t;

typedef struct{

	GPIO_RegDef_t *pGPIO_X_BaseAddr; //wskaznik na adres bazowy peripherala GPIO- wybieramy sobie ktory chcemy obslugiwac w tej funkcji
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;


//GPIO Pin possible modes

//non-interrupt part
#define GPIO_Mode_Input 		0
#define GPIO_Mode_Output 		1
#define GPIO_Mode_Alternate 	2
#define GPIO_Mode_Analog 		3
//interrupt part
#define GPIO_MODE_IT_FT			4	// falling (trigger) edge direction
#define GPIO_MODE_IT_RT			5	// rising (trigger) edge direction
#define GPIO_MODE_IT_RFT		6	// rising/falling (trigger) edge direction






//GPIO pull-up/pull-down values
#define None_pupd 				0
#define Pull_up 				1
#define Pull_down 				2
#define Reserved 				3

//GPIO Speed
#define low_speed 				0
#define	medium_speed			1
#define	fast_speed				2
#define	high_speed				3

/*
 * @GPIO_PIN_AF_MODES
*/
#define GPIO_AF0_SYSTEM        0  // System (JTAG, SWD, RTC)
#define GPIO_AF1_TIM1_2        1  // Timer 1 i Timer 2 (np. PWM dla dźwięku)
#define GPIO_AF2_TIM3_5        2  // Timer 3, 4 i 5
#define GPIO_AF3_TIM9_11       3  // Timer 9, 10 i 11
#define GPIO_AF4_I2C1_3        4  // I2C1, I2C2, I2C3 (np. czujniki, ekrany OLED)
#define GPIO_AF5_SPI1_4        5  // SPI1, SPI2, SPI3, SPI4 (szybkie ekrany LCD)
#define GPIO_AF6_SPI2_5        6  // SPI2, SPI3, SPI4, SPI5
#define GPIO_AF7_USART1_2      7  // USART1 i USART2 (komunikacja z PC / Bluetooth)
#define GPIO_AF8_USART6        8  // USART6
#define GPIO_AF9_I2C2_3        9  // I2C2, I2C3
#define GPIO_AF10_OTG_FS       10 // USB On-The-Go (klawiatura USB, mysz)
#define GPIO_AF11              11 // Rezerwowane
#define GPIO_AF12_SDIO         12 // Karta SD (zapisywanie stanów gry)
#define GPIO_AF13              13 // Rezerwowane
#define GPIO_AF14              14 // Rezerwowane
#define GPIO_AF15_EVENTOUT     15 // Wyjście zdarzeń systemowych


void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOX, uint8_t EnableOrDisable);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOX);
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOX);
void GPIO_WrtieToOutputPort(GPIO_RegDef_t *pGPIOX, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber);
void GPIO_IRinterruptQConfig(uint8_t IRQNumber, uint8_t EnodDi);
void GPIO_PriorityConfig(uint8_t Priority, uint8_t IRQNumber);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* GPIO_DRIVER_API_H_ */
