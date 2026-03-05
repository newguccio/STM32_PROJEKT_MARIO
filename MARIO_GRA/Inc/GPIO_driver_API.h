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
#define GPIO_MODE_IT_FT			4	// falling edge direction
#define GPIO_MODE_IT_RT			5	// rising edge direction
#define GPIO_MODE_IT_RFT		6	// rising/falling edge direction






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






// FUNKCJE POD GPIO API

//clock enable/disable function for GPIO
void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOX, uint8_t EnableOrDisable){
	if(EnableOrDisable ==1){
		if(pGPIOX == GPIO_A){
			RCC->ahb1enr.gpio_A =1;
		}
		else if(pGPIOX == GPIO_B){
			RCC->ahb1enr.gpio_B =1;
		}
		else if(pGPIOX == GPIO_C){
			RCC->ahb1enr.gpio_C =1;
			}
		else if(pGPIOX == GPIO_D){
			RCC->ahb1enr.gpio_D =1;
			}
		else if(pGPIOX == GPIO_E){
			RCC->ahb1enr.gpio_E =1;
			}
		else if(pGPIOX == GPIO_H){
			RCC->ahb1enr.gpio_H =1;
					}
	}
	else{
		if(pGPIOX == GPIO_A){
			RCC->ahb1enr.gpio_A =0;
		}
		else if(pGPIOX == GPIO_B){
			RCC->ahb1enr.gpio_B =0;
		}
		else if(pGPIOX == GPIO_C){
			RCC->ahb1enr.gpio_C =0;
			}
		else if(pGPIOX == GPIO_D){
			RCC->ahb1enr.gpio_D =0;
			}

		else if(pGPIOX == GPIO_E){
			RCC->ahb1enr.gpio_E =0;
			}
		else if(pGPIOX == GPIO_H){
			RCC->ahb1enr.gpio_H =0;
					}
	}
}

//ustawienie/inicjalizacja pinu zeby zaczal dzialac
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp = 0;
	//to jest non interrupt mode
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_Mode_Analog){
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //bierze pin ktory wybralismy i ustawia mu moder
		pGPIOHandle->pGPIO_X_BaseAddr->moder &= ~(0x11 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //cleac przed ustawieniem
		pGPIOHandle->pGPIO_X_BaseAddr->moder |= temp;
	}
	//interrupt mode
	else{
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){

		}











	}
	temp = 0; // zerowanie po poprzedniej czynnosci
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //bierze pin ktory wybralismy i ustawia speed
		pGPIOHandle->pGPIO_X_BaseAddr->ospeedr &= ~(0x11 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIO_X_BaseAddr->ospeedr |= temp;


	temp = 0; // zerowanie po poprzedniej czynnosci
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPullUpPulldownControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIO_X_BaseAddr->pupdr &= ~(0x11 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIO_X_BaseAddr->pupdr |= temp;

	temp = 0;
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_Mode_Alternate) {

	    uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
	    uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; // To zastępuje Twoje odejmowanie

	    if(temp1 == 1) {
	        // Rejestr HIGH (Piny 8-15)
	        pGPIOHandle->pGPIO_X_BaseAddr->afl_H &= ~(0xF << (4 * temp2)); // clean przed nadpisaniem
	        pGPIOHandle->pGPIO_X_BaseAddr->afl_H |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
	    } else {
	        // Rejestr LOW (Piny 0-7)
	        pGPIOHandle->pGPIO_X_BaseAddr->afl_L &= ~(0xF << (4 * temp2)); // clean przed nadpisaniem
	        pGPIOHandle->pGPIO_X_BaseAddr->afl_L |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
	    }
	}
		//narazie tyle, bo wiecej i tak nie trzeba w mario
}

//reset pinu co byl init, poprzez wejscie do rcc pheripheral reset register
void GPIO_DeInit(GPIO_RegDef_t *pGPIOX){


		if(pGPIOX == GPIO_A){
			RCC->AHB1RSTR |= 1<<0;
			RCC->AHB1RSTR &= ~(1<<0);
		}
		else if(pGPIOX == GPIO_B){
			RCC->AHB1RSTR |= 1<<1;
			RCC->AHB1RSTR &= ~(1<<1);
		}
		else if(pGPIOX == GPIO_C){
			RCC->AHB1RSTR |= 1<<2;
			RCC->AHB1RSTR &= ~(1<<2);
		}
		else if(pGPIOX == GPIO_D){
			RCC->AHB1RSTR |= 1<<3;
			RCC->AHB1RSTR &= ~(1<<3);
		}
		else if(pGPIOX == GPIO_E){
			RCC->AHB1RSTR |= 1<<4;
			RCC->AHB1RSTR &= ~(1<<4);
		}
		else if(pGPIOX == GPIO_H){
			RCC->AHB1RSTR |= 1<<7;
			RCC->AHB1RSTR &= ~(1<<7);
		}

}
//konkretny Pin
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber){

	uint8_t value;
	value = (uint8_t) (pGPIOX->idr>>PinNumber) & (0x1); //przesuwam wartosc inputa i extractuje go do nowej zmiennej ktora returnuje

	return value;
}

//caly port
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOX){

	uint16_t value;
	value = (uint16_t) pGPIOX->idr;//przesuwam wartosc inputa i extractuje go do nowej zmiennej ktora returnuje

	return value;

}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber, uint8_t value){
	if(value == 1){							//jesli chcemy miec wlaczone to daje 3v3 na wybrany PinNumber
		pGPIOX->odr |=	(1 << PinNumber);
	}else {

		pGPIOX->odr &= ~(1 <<PinNumber);
	}
}

void GPIO_WrtieToOutputPort(GPIO_RegDef_t *pGPIOX, uint16_t value){
	pGPIOX->odr = value; //uzytkownik wprowadza maske i bezposrednio wrzuca na odr dzieki czemu moze zapalic jakie chce diody a nie tylko konkretne
}


//raczej rzadko uzywana funkcja bardziej jak chcemy ustawic jakis pin na szybko ktory ma podpieta diode i wtedy mozemy sobie cos sprawdzac
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber){
	pGPIOX->odr ^= (1 << PinNumber); // xor czyli wpisuje zawsze przeciwny stan
}



void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnodDi); //enodi-enable or disable
void GPIO_IRQHandling(uint8_t PinNumber);















#endif /* GPIO_DRIVER_API_H_ */
