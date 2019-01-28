#include <stm32f0xx.h>
#include "soft_timer.h"

int main(void)
{
	systimer_init();
	
//GPIO LED Set
	//RCC Set
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//Set PA4 Output
	GPIOA->MODER = (GPIOA->MODER & (~(GPIO_MODER_MODER4_Msk))) | GPIO_MODER_MODER4_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOA->ODR |= GPIO_ODR_4;

//Set Timer
	softtimer_t systimer;
	softtimer_set(&systimer, 1000);

	while(1)
	{
		if(softtimer_is_hit(&systimer))
		{
			GPIOA->ODR ^= GPIO_ODR_4;
			softtimer_set(&systimer, 1000);
		}
	}
}
