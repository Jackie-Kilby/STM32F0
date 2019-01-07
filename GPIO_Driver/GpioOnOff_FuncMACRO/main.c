#include "gpio.h"

#define GPIO_LED	(4)
	
int main(void)
{
	//Init LED GPIO
	GPIO_ENABLE(A);
	GPIO_SET_MODE_OUTPUT(A,4);
	
	//Set PA5 Input
	GPIO_SET_MODE_INPUT(A,5);
	//Read PA5
	while(1)
	{
		if(GPIOA->IDR & GPIO_IDR_5)
		{
			//Set GPIO Up
			GPIO_SET_UP(A, 4);
		}
		else
		{
			//Set GPIO Down
			GPIO_SET_DOWN(A, 4);
		}
	}
}

