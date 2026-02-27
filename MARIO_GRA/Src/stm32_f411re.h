#ifndef stm32_registers
#define stm32_registers

//offset 0x30
typedef struct{
	uint32_t gpio_A : 1;
	uint32_t gpio_B : 1;
	uint32_t gpio_C : 1;
	uint32_t gpio_D : 1;
	uint32_t gpio_E : 1;
	uint32_t reserved1 : 4;
	uint32_t gpio_H : 1;
	uint32_t reserved2 : 8;
	uint32_t CRC : 2;
	uint32_t reserved3 : 16;
	uint32_t DMA1 : 2;
	uint32_t DMA2 : 2;
	uint32_t reserved4 : 18;
}RCC_AHB1ENR_t;



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

typedef struct{


uint32_t tim2 :1;
uint32_t tim3 :1;
uint32_t tim4 :1;
uint32_t tim5 :1;
uint32_t reserved1 :7;
uint32_t wwdg :1;
uint32_t reserved2 :2;
uint32_t spi2 :1;
uint32_t spi3 :1;
uint32_t reserved3 :1;
uint32_t usart2 :1;
uint32_t reserved4 :3;
uint32_t i2c_1 :1;
uint32_t i2c_2 :1;
uint32_t i2c_3 :1;
uint32_t reserved5 :4;
uint32_t pwr :1;
uint32_t reserved6 :3;

}RCC_APB1ENR_t;


#endif
