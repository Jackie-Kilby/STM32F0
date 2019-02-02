#include "compile.h"
#include "soft_timer.h"
#include "led.h"
#include "sys_clock.h"
#include "sys_timer.h"
#include "uart.h"

int main(void)
{
	//Set SysClock as PLL(48MHz)
	sysclock_init_use_pll();
		
	//USART1 Tx Func.
	usart_init();
	
	//Init SoftTimer
	sys_timer_init();
	soft_timer_t systimer;
	soft_timer_set_start_point(&systimer);
	soft_timer_set_timeout(&systimer, 10);
	
	while(1)
	{
		if(soft_timer_is_timeout(&systimer))					
		{
			soft_timer_set_start_point(&systimer);
			soft_timer_set_timeout(&systimer, 100);
			usart_write("USART is ongoing.\n\r", 20);
		}
		//Step6. Write data
		usart_Task();
	}
	
}





#if 0 

uint16_t auto_test_motor_run = 0;
extern int flag_motor_run;

int main(void)
{
	//System Clock Set
	sysclock_init_use_pll();

	led_init();

	//Set Timer	
	sys_timer_init();
	soft_timer_t systimer;
	soft_timer_set_start_point(&systimer);
	soft_timer_set_timeout(&systimer, 10);

	while(1)
	{
		//10ms task
		if(soft_timer_is_timeout(&systimer))					
		{
			soft_timer_set_start_point(&systimer);
			soft_timer_set_timeout(&systimer, 10);
			LED_StateMachine();
			
			//Auto Test for Motor Run
			auto_test_motor_run++;
			if(auto_test_motor_run > 1000)
			{
				flag_motor_run = 1;
				if(auto_test_motor_run > 1300)
				{
					flag_motor_run = 0;
					auto_test_motor_run = 0;
				}
			}
		}
		
	}
}
#endif
