#include "timer.h"

void timer3_init(void)
{
	//Select HSI as system clock
	RCC->CFGR &= ~RCC_CFGR_SW;
	//Set a timer with TIM3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->CR1 &= ~TIM_CR1_CKD;
	TIM3->CR1 |= TIM_CR1_ARPE;
	TIM3->CR1 &= ~TIM_CR1_DIR;
	TIM3->CR1 &= ~TIM_CR1_OPM;
	TIM3->PSC = 0x0;
	TIM3->CNT = 0x0;
	TIM3->ARR = 8000U;
	
}
void timer3_start(void)
{
	TIM3->CR1 |= TIM_CR1_CEN;
}
void timer3_stop(void)
{
	TIM3->CR1 &= ~TIM_CR1_CEN;
}
int timer3_is_hit(void)
{
	return (TIM3->SR) & TIM_SR_UIF;
}

