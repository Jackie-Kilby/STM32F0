#include "gpio.h"

void gpio_a_set_dir(uint8_t pin, uint8_t io_put);
void gpio_b_set_dir(uint8_t pin, uint8_t io_put);

/******************************************************
Func Name	: gpio_init
Return 		:	void
Parameters: char port: GPIOA as 'A', GPIOB as 'B'...
					uint8_t pin: the pin num of GPIO to be set
					uint8_t io_put: the i/o direction the pin to be set
Descript	: Enable the bundle of GPIOs specified in Params
Developer	: Jack Kilby
Update		: 2018-12-27
******************************************************/
void gpio_init(char port, uint8_t pin, uint8_t io_put)
{
	switch(port)
	{
		case 'A':
			RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
			gpio_a_set_dir(pin, io_put);
			break;
		
		case 'B':
			RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
			gpio_b_set_dir(pin, io_put);
			break;
		
		//...
		
		default:
			break;
	}
}

/******************************************************
Func Name	: gpio_x_set_dir
Return 		:	void
Parameters: uint8_t	pin	:	IO number ,such 'GPIO-PA5' as '5'...
					uint8_t io_put:	input is 1, output is 0
Descript	: Set specified GPIO on port X as input or output
Developer	: Jack Kilby
Update		: 2018-12-27
******************************************************/
void gpio_a_set_dir(uint8_t pin, uint8_t io_put)
{
	if(io_put)
	{
		//Set GPIO MODER input
	}
	else
	{
		// Set GPIO MODER output
		GPIO_A_SET_MODE_OUTPUT(pin);
				
		// Set GPIO OSPEEDR
		GPIO_A_SET_SPEED_HIGH(pin);
	}
}
void gpio_b_set_dir(uint8_t pin, uint8_t io_put)
{
	if(io_put)
	{
		//Set GPIO MODER input
	}
	else
	{
		//for B, not defined till now
	}
}

/******************************************************
Func Name	: gpio_set_up
Return 		:	void
Parameters: char 		port: GPIOA as 'A', GPIOB as 'B'...
						uint8_t	pin	:	IO number ,such 'GPIO-PA5' as '5'...
Descript	: Set specified GPIO up/down
Developer	: Jack Kilby
Update		: 2018-12-27
******************************************************/
void gpio_set_up(char port, uint8_t pin)
{
	switch(port)
	{
		case 'A':
			GPIO_A_SET_UP(pin);
			break;
		
		case 'B':
			break;
		
		default:
			break;
	}
	
}
void gpio_set_down(char port, uint8_t pin)
{
	switch(port)
	{
		case 'A':
			GPIO_A_SET_DOWN(pin);
			break;
		
		case 'B':
			break;
		
		default:
			break;
	}
}
/******************************************************
******************************************************/

