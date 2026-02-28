/*
 * joystick.c
 *
 *  Created on: 28 lut 2026
 *      Author: hasom
 */
#include  <stdint.h>
#include  <stdio.h>
#include "stm32_f411re.h"

//wykonuje sie raz zeby wszystko włączyc i przygotowac do pracy
void ADC_ON(void){

	RCC->apb2enr.adc1 |= 1;  //odpalenie szyny apb2 bo tam jest adc1
	GPIO_A->moder |= (3<<0) | (3<<2); //ustawienie PA0 i PA1 na tryb analogowy
	ADC1->ADC_CR2 |= (1<<0); //ustawienie ADON na 1
	ADC1->adc_smpr2 |= (7<<0); //ustawienie probkowania na max cykle
}



uint32_t ADC_Control_Read(void){

ADC1->ADC_CR2 |=(1<<30); // SWSTART, 1 startuje konwersje

//spowolnienie procesora: jesli nie ma 1 na eoc czekaj, bo 1 oznacza koniec, czyli pozycja zczytana
while ( !(ADC1->SR & (1 << 1) ) ){

}

// end of corvesion sygnalizuje koniec przetwarzania danej

return ADC1->dr;
}
