#include <stm32f0xx.h>
#include <stdint.h>
#include "led.h"

int main(void)
{
	//RCC Set
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//Set PA4 Output
	GPIOA->MODER = (GPIOA->MODER & (~(GPIO_MODER_MODER4_Msk))) | GPIO_MODER_MODER4_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOA->ODR |= GPIO_ODR_4;
	
	//Set PA5 Input
	GPIOA->MODER &= ~GPIO_MODER_MODER5;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;
			
	while(1)
	{	
		//get led_signal
		LED_StateMachine();
	}
}








