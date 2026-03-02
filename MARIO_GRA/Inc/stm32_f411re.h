#ifndef stm32_registers
#define stm32_registers
// #include<stdint.h> trzeba czy nie? u zioma trzeba z poradnika
//offset 0x30
typedef struct{

	volatile 	uint32_t gpio_A : 1;
	volatile 	uint32_t gpio_B : 1;
	volatile	uint32_t gpio_C : 1;
	volatile	uint32_t gpio_D : 1;
	volatile	uint32_t gpio_E : 1;
	volatile	uint32_t reserved1 : 2;
	volatile	uint32_t gpio_H : 1;
	volatile	uint32_t reserved2 : 4;
	volatile	uint32_t CRC : 1;
	volatile	uint32_t reserved3 : 8;
	volatile	uint32_t DMA1 : 1;
	volatile	uint32_t DMA2 : 1;
	volatile	uint32_t reserved4 : 9;

}RCC_AHB1ENR_t;


//apb1 enable register
typedef struct{

	volatile uint32_t tim2 :1;
	volatile uint32_t tim3 :1;
	volatile uint32_t tim4 :1;
	volatile uint32_t tim5 :1;
	volatile uint32_t reserved1 :7;
	volatile uint32_t wwdg :1;
	volatile uint32_t reserved2 :2;
	volatile uint32_t spi2en :1;
	volatile uint32_t spi3en :1;
	volatile uint32_t reserved3 :1;
	volatile uint32_t usart2 :1;
	volatile uint32_t reserved4 :3;
	volatile uint32_t i2c_1 :1;
	volatile uint32_t i2c_2 :1;
	volatile uint32_t i2c_3 :1;
	volatile uint32_t reserved5 :4;
	volatile uint32_t pwr :1;
	volatile uint32_t reserved6 :3;

}RCC_APB1ENR_t;

//apb2 enable register
typedef struct{

	volatile uint32_t tim1 :1;
	volatile uint32_t reserved1 :3;
	volatile uint32_t usart1:1;
	volatile uint32_t usart6:1;
	volatile uint32_t reserved2 :2;
	volatile uint32_t adc1:1;
	volatile uint32_t reserved3 :2;
	volatile uint32_t sdioen:1;
	volatile uint32_t spi1en:1;
	volatile uint32_t spi4en:1;
	volatile uint32_t syscfG:1;
	volatile uint32_t reserved4 :1;
	volatile uint32_t tim9 :1;
	volatile uint32_t tim10 :1;
	volatile uint32_t tim11 :1;
	volatile uint32_t reserved5 :1;
	volatile uint32_t spi5en :1;
	volatile uint32_t reserved6 :11;

}RCC_APB2ENR_t;

//ogolnie caly blok pamieci dla RCC a te na gorze to bitmapy wybranych szyn ktore potem mozna wpisac tutaj jaki definicje struktury odpowiedniej, dzieki temu mozemy miec w jednej zmiennej
//bardzo konkretny dostep do wybranych bitów/pinow/itpitd
typedef struct{

		volatile uint32_t CR;            // 0x00 -offsety co 4 jak w gpio_typedef
	    volatile uint32_t PLLCFGR;       // 0x04
	    volatile uint32_t CFGR;          // 0x08
	    volatile uint32_t CIR;           // 0x0C
	    volatile uint32_t AHB1RSTR;      // 0x10
	    volatile uint32_t AHB2RSTR;      // 0x14
	    volatile uint32_t reserved1;     // 0x18
		volatile uint32_t reserved2; 	 // 0x1C
		volatile uint32_t apb1rstr;		//0x20
		volatile uint32_t apb2rstr;		//0x24
		volatile uint32_t reserved3;     //0x28
		volatile uint32_t reserved4;	//0x2C
		volatile RCC_AHB1ENR_t ahb1enr;     // 0x30
		volatile uint32_t ahb2enr;		//0x34
		volatile uint32_t reserved5;     //0x38
		volatile uint32_t reserved6;	//0x3C
		volatile RCC_APB1ENR_t apb1enr; 		//0x40
		volatile RCC_APB2ENR_t apb2enr;		//0x44
		volatile uint32_t reserved7;     //0x48
		volatile uint32_t reserved8;	//0x4C
		volatile uint32_t ahb1_Lenr; 		//0x50
		volatile uint32_t ahb2_Lenr;		//0x54
		volatile uint32_t reserved9;   		  //0x58
		volatile uint32_t reserved10;		//0x5C
		volatile uint32_t apb1_Lenr; 		//0x60
		volatile uint32_t apb2_Lenr;		//0x64
		volatile uint32_t reserved11;    	 //0x68
		volatile uint32_t reserved12;		//0x6C
		volatile uint32_t bdcr;     		//0x70
		volatile uint32_t csr;				//0x74
		volatile uint32_t reserved13;    	//0x78
		volatile uint32_t reserved14;		//0x7C
		volatile uint32_t sscgr;     		//0x80
		volatile uint32_t cfgr;				//0x84
		volatile uint32_t dckcfgr;			//0x88

}RCC_TypeDef_t;


// moge tak zrobic,sa co 4 bajty i zgadza sie w takiej kolejnosci z offsetem w dokumentacji
typedef struct{

	volatile	uint32_t moder;     // offsety: 0x00
	volatile	uint32_t otyper;	//			0x04
	volatile	uint32_t ospeedr;	//			0x08
	volatile	uint32_t pupdr;		//			0x0C
	volatile	uint32_t idr;		//			0x10
	volatile	uint32_t odr;		//			0x14
	volatile	uint32_t bsrr;		//			0x18
	volatile	uint32_t lckr;		//			0x1C
	volatile	uint32_t afl_L;		//			0x20
	volatile	uint32_t afl_H;		//			0x24

}GPIO_RegDef_t;

typedef struct{

	volatile uint32_t SR;            // 0x00 -offsety co 4 jak w gpio_typedef
    volatile uint32_t ADC_CR1;       // 0x04
    volatile uint32_t ADC_CR2;        // 0x08
    volatile uint32_t adc_smpr1;      // 0x0C
    volatile uint32_t adc_smpr2;     // 0x10
    volatile uint32_t jofr1;      	// 0x14
    volatile uint32_t jofr2;     	// 0x18
	volatile uint32_t jofr3; 		 // 0x1C
	volatile uint32_t jofr4;		//0x20
	volatile uint32_t htr;			//0x24
	volatile uint32_t Ltr;    		 //0x28
	volatile uint32_t sqr1;			//0x2C
	volatile uint32_t sqr2;   	 	 // 0x30
	volatile uint32_t sqr3;			//0x34
	volatile uint32_t jsqr;    		 //0x38
	volatile uint32_t jdr1;			//0x3C
	volatile uint32_t jdr2; 		//0x40
	volatile uint32_t jdr3;			//0x44
	volatile uint32_t jdr4;   		  //0x48
	volatile uint32_t dr;			//0x4C

}ADC_TypeDef_t;


// definiujemy RCC zeby bylo do maina (poprzez typecasting do wskaznika), a adresem jest poczatek calego modulu RCC, wiec mozemy strzalkowac do jego wnetrza a potem uzywac . jako co konkretnie zmienamy
#define RCC ((RCC_TypeDef_t*)0x40023800U) //U zeby bylo wiadomoze liczba bez znaku
#define ADC1 ((ADC_TypeDef_t*)0x40012000U)

#define GPIO_A ((GPIO_RegDef_t*)0x40020000)
#define GPIO_B ((GPIO_RegDef_t*)0x40020400)
#define GPIO_C ((GPIO_RegDef_t*)0x4002800)
#define GPIO_D ((GPIO_RegDef_t*)0x40020C00)
#define GPIO_E ((GPIO_RegDef_t*)0x40021000)
#define GPIO_H ((GPIO_RegDef_t*)0x40021C00)




// te na gorze GPIO_RegDef_t jest zamiast tego
/*
typedef struct{

	uint32_t pin0 :2;
	uint32_t pin1 :2;
	uint32_t pin2 :2;
	uint32_t pin3 :2;
	uint32_t pin4 :2;
	uint32_t pin5 :2;
	uint32_t pin6 :2;
	uint32_t pin7 :2;
	uint32_t pin8 :2;
	uint32_t pin9 :2;
	uint32_t pin10 :2;
	uint32_t pin11 :2;
	uint32_t pin12 :2;
	uint32_t pin13 :2;
	uint32_t pin14 :2;
	uint32_t pin15 :2;

}GPIOx_MODE_t;

typedef struct {

	uint32_t pin0 :1;
	uint32_t pin1 :1;
	uint32_t pin2 :1;
	uint32_t pin3 :1;
	uint32_t pin4 :1;
	uint32_t pin5 :1;
	uint32_t pin6 :1;
	uint32_t pin7 :1;
	uint32_t pin8 :1;
	uint32_t pin9 :1;
	uint32_t pin10 :1;
	uint32_t pin11 :1;
	uint32_t pin12 :1;
	uint32_t pin13 :1;
	uint32_t pin14 :1;
	uint32_t pin15 :1;
	uint32_t reserved :16;

}GPIOx_ODR_t;

typedef struct {

	uint32_t pin0 :1;
	uint32_t pin1 :1;
	uint32_t pin2 :1;
	uint32_t pin3 :1;
	uint32_t pin4 :1;
	uint32_t pin5 :1;
	uint32_t pin6 :1;
	uint32_t pin7 :1;
	uint32_t pin8 :1;
	uint32_t pin9 :1;
	uint32_t pin10 :1;
	uint32_t pin11 :1;
	uint32_t pin12 :1;
	uint32_t pin13 :1;
	uint32_t pin14 :1;
	uint32_t pin15 :1;
	uint32_t reserved :16;

}GPIOx_IDR_t;

*/

#endif
