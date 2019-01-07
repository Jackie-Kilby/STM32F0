#include "gpio.h"

/******************************************************
Func Name	: gpio_init
Return 		:	void
Parameters: char port: GPIOA as 'A', GPIOB as 'B'...
Descript	: Enable the bundle of GPIOs specified in Params
Developer	: Jack Kilby
Update		: 2019-01-02
******************************************************
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

******************************************************
Func Name	: gpio_set_dir
Return 		:	void
Parameters: GPIO_TypeDef * port: GPIOA as 'GPIOA'...
						uint8_t	pin	:	IO number ,such 'GPIO-PA5' as '5'...
					uint8_t io_put:	input is '1', output is '0'
Descript	: Set specified GPIO as output or input
Developer	: Jack Kilby
Update		: 2019-01-02
******************************************************
void gpio_set_dir(GPIO_TypeDef * port, uint8_t pin, uint8_t io_put)
{
	if(io_put)
	{
		//Set GPIO MODER input
	}
	else
	{
		GPIO_SET_MODE_OUTPUT(A,pin);
	}
}

******************************************************
Func Name	: gpio_set_up/down
Return 		:	void
Parameters: GPIO_TypeDef *port: struct point of port, such as GPIOA as GPIOA...
						uint8_t	pin	:	IO number ,such 'GPIO-PA5' as '5'...
Descript	: Set specified GPIO up/down
Developer	: Jack Kilby
Update		: 2019-01-02
******************************************************
void gpio_set_up(GPIO_TypeDef * port, uint8_t pin)
{
		GPIO_SET_UP(A, pin);
}

void gpio_set_down(GPIO_TypeDef * port, uint8_t pin)
{
		GPIO_SET_DOWN(A,pin);
}
******************************************************
******************************************************/

