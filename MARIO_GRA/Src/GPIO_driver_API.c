/*
 * GPIO_driver_API.c
 *
 *  Created on: 8 mar 2026
 *      Author: hasom
 */

#include "GPIO_driver_Api.h"




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
		pGPIOHandle->pGPIO_X_BaseAddr->moder &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clear przed ustawieniem
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //bierze pin ktory wybralismy i ustawia mu moder
		//pGPIOHandle->pGPIO_X_BaseAddr->moder &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clear przed ustawieniem
		pGPIOHandle->pGPIO_X_BaseAddr->moder |= temp;
	}
	//interrupt mode
	else{
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // ustawiamy falling edge, a nie wiemy czy wczesniej nie byl trigger edge wiec prowizorycznie zerujemy pozycje risingedge
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);// zerujemy na wszelki rising edge

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		uint8_t temp1 = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) / 4); //jest INTEGER wiec wynik to liczba calkowita wiec jesli podzielic numer pinu przez 4(bo tyle jest bitów na kazdy element) to wskaze numer tablicy exticr[] do ktorej trzeba wpisac, np PA13 -> 13/4 = 3 wiec exticr[3] (exticr4)-> teraz ktory bit w tej tablicy
		uint8_t temp2 = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) % 4);	//wynik to reszta dzielenia przez 4(bo tyle jest w rejestrze exti[i]) więc, wartosc temp2 bedzie wynosic dokladne miejsce w juz wybranej tablicy, np PA13 -> 13%4 = 1 wiec w exticr2 na pozycji 1
		uint8_t port_code;
		if(pGPIOHandle->pGPIO_X_BaseAddr == GPIO_A) port_code = 0;
		else if(pGPIOHandle->pGPIO_X_BaseAddr == GPIO_B) port_code = 1;
		else if(pGPIOHandle->pGPIO_X_BaseAddr == GPIO_C) port_code = 2;
		else if(pGPIOHandle->pGPIO_X_BaseAddr == GPIO_D) port_code = 3;
		else if(pGPIOHandle->pGPIO_X_BaseAddr == GPIO_E) port_code = 4;
		else if(pGPIOHandle->pGPIO_X_BaseAddr == GPIO_H) port_code = 5;

		SYSCFG->exticr[temp1] |= ( port_code << 4*temp2);

		EXTI->IMR  |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // enable interrupt mask
	}
	temp = 0; // zerowanie po poprzedniej czynnosci
		pGPIOHandle->pGPIO_X_BaseAddr->ospeedr &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //bierze pin ktory wybralismy i ustawia speed
		//pGPIOHandle->pGPIO_X_BaseAddr->ospeedr &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIO_X_BaseAddr->ospeedr |= temp;


	temp = 0; // zerowanie po poprzedniej czynnosci
		pGPIOHandle->pGPIO_X_BaseAddr->pupdr &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPullUpPulldownControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	//	pGPIOHandle->pGPIO_X_BaseAddr->pupdr &= ~(0x3 << 2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
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
	pGPIOX->odr = value; 										//uzytkownik wprowadza maske i bezposrednio wrzuca na odr dzieki czemu moze zapalic jakie chce diody a nie tylko konkretne
}


//raczej rzadko uzywana funkcja bardziej jak chcemy ustawic jakis pin na szybko ktory ma podpieta diode i wtedy mozemy sobie cos sprawdzac
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOX, uint8_t PinNumber){
	pGPIOX->odr ^= (1 << PinNumber); 									// xor czyli wpisuje zawsze przeciwny stan
}





//enodi-enable or disable
void GPIO_IRinterruptQConfig(uint8_t IRQNumber, uint8_t EnodDi){
	if(EnodDi == 1){
		if(IRQNumber <= 31){
			*NVIC_ISER0 |= (1<<IRQNumber);
		}
		else if(IRQNumber >= 32 && IRQNumber<=63){

			*NVIC_ISER1 |= (1<< (IRQNumber%32));// bo jak mamy np 33 to by chcialo sie wpisac w 33 miejscu a 33 powinien byc na bicie nr 1 w ISER1 wiec modulus to zrobi
		}
		else if(IRQNumber >= 64 && IRQNumber<=95){
			*NVIC_ISER2 |= (1<< (IRQNumber%64));
		}
		else if(IRQNumber >= 96 && IRQNumber<=127){
			*NVIC_ISER3 |= (1<< (IRQNumber%96));
		}
	}
		else{
			if(IRQNumber <= 31){
						*NVIC_ICER0 |= (1<<IRQNumber);
					}
					else if(IRQNumber >= 32 && IRQNumber<=63){

						*NVIC_ICER1 |= (1<< (IRQNumber%32));// bo jak mamy np 33 to by chcialo sie wpisac w 33 miejscu a 33 powinien byc na bicie nr 1 w ISER1 wiec modulus to zrobi
					}
					else if(IRQNumber >= 64 && IRQNumber<=95){
						*NVIC_ICER2 |= (1<< (IRQNumber%64));
					}
					else if(IRQNumber >= 96 && IRQNumber<=127){
						*NVIC_ICER3 |= (1<< (IRQNumber%96));
					}
			}
}
void GPIO_PriorityConfig(uint8_t IRQPriority, uint8_t IRQNumber){

	uint8_t iprx = IRQNumber /4;	// sprawdzaymy do ktroego z 60 rejestrow priority
	uint8_t iprx_section = IRQNumber % 4;	//sprawdzamy na ktora z 4 pozycji w dobranym rejestrze
	uint8_t shiftammount = ( (iprx_section*8) +4); //o ile przesunac zeby wpisac w ktoras z obliczonych 4 pozycji z uzwgledniemie ze 4 najmlodsze bity musza byc zerami
	*(NVIC_IPR_BaseAddr + iprx) &= ~(0xF << shiftammount); // clear przed wpisaniem
	*(NVIC_IPR_BaseAddr + iprx ) |= (IRQPriority << shiftammount);	//wpisanie do rejestru

}

void GPIO_IRQHandling(uint8_t PinNumber){

	if (EXTI->PR & (1 << PinNumber)) {

	        EXTI->PR |= (1 << PinNumber); // Jeśli tak, to ją czyścimy wpisując 1
	    }
}
