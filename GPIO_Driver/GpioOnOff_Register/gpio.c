#include "gpio.h"

GPIO_TypeDef * GpioGroup[3] = {GPIOA, GPIOB, GPIOC};
/******************************************************
Func Name	: gpio_init
Return 		:	void
Parameters: char port: GPIOA as 'A', GPIOB as 'B'...
Descript	: Enable the bundle of GPIOs specified in Params
Developer	: Jack Kilby
Update		: 2019-01-02
******************************************************/
void gpio_init(char port)
{
	switch(port)
	{
		case 'A':
			RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
			break;
		
		case 'B':
			RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
			break;
		
		//...
		
		default:
			break;
	}
}

/******************************************************
Func Name	: gpio_set_dir
Return 		:	void
Parameters: GPIO_TypeDef * port: GPIOA as 'GPIOA'...
						uint8_t	pin	:	IO number ,such 'GPIO-PA5' as '5'...
					uint8_t io_put:	input is '1', output is '0'
Descript	: Set specified GPIO as output or input
Developer	: Jack Kilby
Update		: 2019-01-02
******************************************************/
void gpio_set_dir(GPIO_TypeDef * port, uint8_t pin, uint8_t io_put)
{
	if(io_put)
	{
		//Set GPIO MODER input
	}
	else
	{
		port->MODER = (port->MODER & ~(GPIO_MODER_MASK << 2*pin)) | GPIO_MODER_OUTPUT << 2*pin;
		port->OSPEEDR |= GPIO_OSPEEDR_HIGH << 2*pin;
	}
}

/******************************************************
Func Name	: gpio_set_up/down
Return 		:	void
Parameters: GPIO_TypeDef *port: struct point of port, such as GPIOA as GPIOA...
						uint8_t	pin	:	IO number ,such 'GPIO-PA5' as '5'...
Descript	: Set specified GPIO up/down
Developer	: Jack Kilby
Update		: 2019-01-02
******************************************************/
void gpio_set_up(GPIO_TypeDef * port, uint8_t pin)
{
	if((port == GPIOA) || (port == GPIOB) || (port == GPIOC))
	
	//if port is GPIOA/B/C/D
	int i = 0;
	for(i=0 ; i<3 ; ++i)
	{
		if(&GpioGroup[i] == &port)
		{
			port->ODR |= GPIO_ODR_SET_BIT << pin;
		}
	}
	
	
		
}

void gpio_set_down(GPIO_TypeDef * port, uint8_t pin)
{
	port->ODR &= ~(GPIO_ODR_SET_BIT << pin);
}
/******************************************************
******************************************************/

