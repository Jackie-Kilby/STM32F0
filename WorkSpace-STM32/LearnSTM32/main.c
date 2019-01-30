#include "compile.h"
#include "soft_timer.h"
#include "led.h"


uint16_t auto_test_motor_run = 0;
extern int flag_motor_run;
int main(void)
{
	systimer_init();
//GPIO LED Set
	led_init();

//Set Timer	
	systimer_init();

	softtimer_t systimer;
	softtimer_set(&systimer, 10);

	while(1)
	{
		if(softtimer_is_hit(&systimer))					//10ms task
		{
			softtimer_set(&systimer, 10);
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
