#include "sys_clock.h"

uint32_t g_sys_clock = 8000;

void sysclock_init_use_hsi(void)
{
	//STM32F0 HSI = 8MHz
	RCC->CR |= RCC_CR_HSION; 
	while(!(RCC->CR & (RCC_CR_HSIRDY_Msk)));
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	
	//for SYSCLK(8MHz) < 24MHz, need to set LATENCY = 000, means Wait State = 0
	FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
	
	//Set sys_clock global param
	g_sys_clock = 8000;
}

void sysclock_init_use_hse(void)
{
	//HSE = 8MHz
	RCC->CR |= RCC_CR_HSEON; 
	while(!(RCC->CR & (RCC_CR_HSERDY_Msk)));
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= RCC_CFGR_SW_HSE;
	//for SYSCLK(8MHz) < 24MHz, need to set LATENCY = 000, means Wait State = 0
	FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
	/*if SYSCLK > 24MHz, need to set LATENCY = 001
	FLASH->ACR |= FLASH_ACR_LATENCY;*/
	
	//Set sys_clock global param
	g_sys_clock = 8000;
}
	

void sysclock_init_use_pll(void)
{
	//PLL = 48MHz
	
	//Set Prefetch
	FLASH->ACR |= FLASH_ACR_PRFTBE;
	while(!(FLASH->ACR & FLASH_ACR_PRFTBE));
	
	//if SYSCLK < 24MHz, need to set LATENCY = 000
	FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
	//if SYSCLK > 24MHz, need to set LATENCY = 001
	FLASH->ACR |= FLASH_ACR_LATENCY;
	
	//Config PLL
	RCC->CR &= ~RCC_CR_PLLON;
	while(RCC->CR & RCC_CR_PLLRDY_Msk);
	RCC->CFGR &= ~RCC_CFGR_PLLMUL_Msk;
	RCC->CFGR |= RCC_CFGR_PLLMUL12;
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY_Msk));
	
	//Set sys_clock global param
	g_sys_clock = 48000;
}
