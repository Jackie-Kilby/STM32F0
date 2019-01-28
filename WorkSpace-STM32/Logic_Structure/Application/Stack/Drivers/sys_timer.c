#include <stm32f0xx.h>
#include "sys_timer.h"

uint32_t systimer_cnt = 0;

void TIM14_IRQHandler(void)
{
	TIM14->SR &= ~TIM_SR_UIF_Msk;
	systimer_cnt++;
}

uint32_t systimer_get_current(void)
{
	uint32_t time_current = 0;
	time_current = systimer_cnt*(TIM14->ARR)+(TIM14->CNT);
	return time_current; 				//(systimer_cnt*(TIM14->ARR)+TIM14->CNT);
}


void systimer_init(void)
{
	//TIM14 for System Tick
	//RCC Set
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	//TIM14 Init
	TIM14->CR1 |= TIM_CR1_ARPE;
	TIM14->CR1 &= ~TIM_CR1_UDIS;
	TIM14->CR1 &= ~TIM_CR1_URS;
	TIM14->DIER |= TIM_DIER_UIE;
	
	//TIM14 Config
	TIM14->PSC = 7999U;
	TIM14->ARR = 50000U;
	TIM14->CNT = 0;
	
	//TIM14 Start
	TIM14->DIER |= TIM_DIER_UIE;
	TIM14->CR1 |= TIM_CR1_CEN;

	/*Config NVIC for TIM14*/
	NVIC_EnableIRQ(TIM14_IRQn);
	NVIC_SetPriority(TIM14_IRQn, 0);
}
