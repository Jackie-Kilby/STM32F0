#include "gpio.h"

#define GPIO_LED	(4)
	
int main(void)
{
	//Init LED GPIO
	gpio_init('A', GPIO_LED , 0);
	
	//Set GPIO Up
	gpio_set_up('A', GPIO_LED);
	//Set GPIO Down
	gpio_set_down('A', GPIO_LED);

	while(1);
}

