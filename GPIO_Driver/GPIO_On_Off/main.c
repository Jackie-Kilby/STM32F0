#include <stm32f0xx.h>

int main(void)
{
	//Set RCC to enable GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//Set GPIO register
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_4);
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR4_Msk);
	
	//Set GPIO Down
	GPIOA->ODR &= ~GPIO_ODR_4;
	while(1);
}

