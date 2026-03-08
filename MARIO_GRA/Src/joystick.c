/*
 * joystick.c
 *
 *  Created on: 28 lut 2026
 *      Author: hasom
 */
#include  <stdint.h>
#include  <stdio.h>
#include "GPIO_driver_API.h"

//#include "GPIO_driver_Api.c"
//#include "stm32_f411re.h"

void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOX, uint8_t EnableOrDisable);




//wykonuje sie raz zeby wszystko włączyc i przygotowac do pracy
void ADC_ON(void){

	GPIO_PeripheralClockControl(GPIO_A, 1);			//TO SAMO CO TA BNA DOLE ALE ZROBIONE ŁADNIE W API
//	RCC->ahb1enr.gpio_A =1;							//odpalenie szyny apb2 bo tam jest adc1

	RCC->apb2enr.adc1 = 1;



	GPIO_A->moder |= (3<<0) | (3<<2);	//ustawienie PA0 i PA1 na tryb analogowy
	GPIO_A->moder &= ~(3<<8);
	GPIO_A->pupdr |= (1<<8);

	ADC1->ADC_CR2 |= (1<<0); //ustawienie ADON na 1
	ADC1->adc_smpr2 |= (7<<0) | (7<<3); //ustawienie probkowania na max cykle dla pa0 i pa1 - bez miany tego powinno dzialac

}



uint32_t ADC_Control_Read(uint32_t channel){

//	ADC1->sqr3 &= ~0x3;	moge dac to bo czyszcze tylko dwie pierwsze pozycje 0x011 ale to zly nawyk
ADC1->sqr3 &= ~0x1F; //czyszcisz poprzedni stan przed nowym bo nie da sie zmienic 1 na 0- bez tego nie wie czy lewo/prawo czy szum

ADC1->sqr3 |= channel; //wybor kanalu ktory pierwszy zostanie obliczony w przypadku z drazkiem pozycji X czy Y


ADC1->ADC_CR2 |=(1<<30); // SWSTART, 1 startuje konwersje - bez tego nie ruszy

//spowolnienie procesora: jesli nie ma 1 na eoc czekaj, bo 1 oznacza koniec, czyli pozycja zczytana- bez tego odpierdala
while ( !(ADC1->SR & (1 << 1) ) ){

}

// end of corvesion sygnalizuje koniec przetwarzania danej

return ADC1->dr;
}
