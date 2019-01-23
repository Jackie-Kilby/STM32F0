#include <stm32f0xx.h>
#include <stdint.h>
#include "led.h"
#include "timer.h"
#include "rtc.h"

extern uint32_t rtc_time;

int main(void)
{
#if 0
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
#endif 
	
	//RTC Func Implementation
	//Power Enable
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_DBP;					//DISABLE RTC domain write protection
	
	//Choose LSI as RTC clock
	RCC->CSR |= RCC_CSR_LSION;				//ENABLE LSI
	while(RCC_CSR_LSIRDY!=(RCC->CSR & RCC_CSR_LSIRDY_Msk));	//Check LSI Ready
	RCC->BDCR |= RCC_BDCR_BDRST;
	RCC->BDCR &= ~RCC_BDCR_BDRST;
	RCC->BDCR = (RCC->BDCR & (~(RCC_BDCR_RTCSEL_Msk)))|RCC_BDCR_RTCSEL_1;		//Choose LSI as RTC Clock	
	
	//RTC Enable
	RCC->BDCR |= RCC_BDCR_RTCEN;
#if 0//	
	//RTC Init
	//Give key to RTC Write Protection Reg
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;
	RTC->ISR |= RTC_ISR_INIT;
	while(RTC_ISR_INITF !=((RTC->ISR) & RTC_ISR_INITF));
	
	//RTC Value Init
	RTC->TR = 5U;
	//Exit Init mode by clearing INIT bit.
	RTC->WPR = 0x11;
	RTC->WPR = 0x22;
	RTC->ISR &= ~RTC_ISR_INIT;
#endif
	PWR->CR &= ~PWR_CR_DBP;					//ENABLE RTC domain write protection

	rtc_timer_t timer_1;
	rtc_add_timer(&timer_1, 10);
	
	while(1)
	{
		//RTC read
		rtc_time = rtc_get_time();
		if(rtc_is_timer_hit(&timer_1))
		{
			rtc_time++;
		}
	}
}








