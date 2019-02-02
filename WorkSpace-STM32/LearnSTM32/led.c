#include "led.h"
#include "gpio.h"

void led_init(void)
{
	//RCC Set
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//Set PA4 Output
	GPIO_SET_MODE_OUTPUT(A, 4);
	GPIO_SET_UP(A, 4);
}

/********************************************************************************
Func Name	: led_high
Return 		: void
Parameters	: char port: GPIOA as 'A', GPIOB as 'B'...
			  int  pin : the pin number under the port.
Descript	: Set the led pin voltage high.
Developer	: Jack Kilby
Update		: 2019-01-16
********************************************************************************/
void led_high(char port, int pin)
{
	GPIOA->ODR |= (1 << pin);
}
/********************************************************************************
Func Name	: led_low
Return 		: void
Parameters	: char port: GPIOA as 'A', GPIOB as 'B'...
			  int  pin : the pin number under the port.
Descript	: Set the led pin voltage low.
Developer	: Jack Kilby
Update		: 2019-01-16
********************************************************************************/
void led_low(char port, int pin)
{
	GPIOA->ODR &= ~(1 << pin);
}
#define LED_STATEMACHINLE_IMPLEMENT_METHOD	2
#if (LED_STATEMACHINLE_IMPLEMENT_METHOD == 5)
uint32_t timer_blink = 0;
int flag_motor_run = 0;
void LED_StateMachine(void)
{
	//if(flag_motor_run)
	{
	//	GPIOA->ODR &= ~(1 << 4);
	//	return;
	}
	timer_blink++;
	if(timer_blink > 40)
	{
		timer_blink = 0;
		GPIOA->ODR ^= (1 << 4);
	}
}


#endif 
#if (LED_STATEMACHINLE_IMPLEMENT_METHOD == 2)
#define TIMER_ON_SLOW_BLINK		50
#define TIMER_OFF_SLOW_BLINK	150
#define TIMER_ON_FAST_BLINK		40
#define TIMER_OFF_FAST_BLINK	40
/***************************************************************************************
Func Name	: LED_StateMachine
Return 		: void
Parameters	: void
Descript	: Led State Machine for RealitySwitch
Developer	: Jack Kilby
Update		: 2019-01-29

***************************************************************************************/
typedef enum
{
	LED_IDLE,
	LED_ON,
	LED_FAST_BLINK,
	LED_SLOW_BLINK,
	LED_DOUBLE_BLINK_0,
	LED_DOUBLE_BLINK_1,
	LED_DOUBLE_BLINK_2,
}led_state_t;
led_state_t led_state = LED_IDLE;

int flag_motor_run = 0;
int flag_off_rf = 0;
int flag_is_on_net = 0;
int flag_net_workwell = 0;
int flag_bat_low = 0;
uint32_t timer_blink = 0;
uint32_t timer_double_blink = 0;

void LED_StateMachine(void)
{
	switch(led_state)
	{
		case LED_IDLE:
			if(flag_motor_run)
			{
				led_state = LED_ON;
			}
			else
			{
				if(timer_blink > 0)
					timer_blink--;
				
				if(timer_double_blink > 0)
					timer_double_blink--;
				
				if(0 == timer_blink)
				{
					if(!flag_off_rf)
					{
						if(flag_is_on_net)
						{
							if(!flag_net_workwell)
							{
								timer_blink = TIMER_ON_SLOW_BLINK;
								led_state = LED_SLOW_BLINK;
							}
						}
						else
						{
							timer_blink = TIMER_ON_FAST_BLINK;
							led_state = LED_FAST_BLINK;
						}
					}
				}
				if((flag_bat_low == 1)&&(timer_double_blink == 0))
				{
					timer_double_blink = 10;
					led_state = LED_DOUBLE_BLINK_0;
				}
			}
			
			if(LED_IDLE != led_state)
			{
				led_low('A', GPIO_LED);
			}
			break;
					
		case LED_ON:
			if(!flag_motor_run)
			{
				led_high('A', GPIO_LED);
				led_state = LED_IDLE;
			}
			break;
		
		case LED_FAST_BLINK:
			if(timer_blink > 0)
				--timer_blink;
			if(timer_blink == 0)
			{
				led_high('A',GPIO_LED);
				timer_blink = TIMER_OFF_FAST_BLINK;
				led_state = LED_IDLE;
			}
			break;
			
		case LED_SLOW_BLINK:
			if(timer_blink > 0)
				--timer_blink;
			if(timer_blink == 0)
			{
				timer_blink = TIMER_OFF_SLOW_BLINK;
				led_high('A',GPIO_LED);
				led_state = LED_IDLE;
			}
			break;
			
		case LED_DOUBLE_BLINK_0:
			if(timer_double_blink > 0)
				--timer_double_blink;
			if(timer_double_blink == 0)
			{
				timer_double_blink = 10;
				led_high('A',GPIO_LED);
				led_state = LED_DOUBLE_BLINK_1;
			}
			break;
			
		case LED_DOUBLE_BLINK_1:
			if(timer_double_blink > 0)
				--timer_double_blink;
			if(timer_double_blink == 0)
			{
				timer_double_blink = 10;
				led_low('A',GPIO_LED);
				led_state = LED_DOUBLE_BLINK_2;
			}
			break;
			
		case LED_DOUBLE_BLINK_2:
			if(timer_double_blink > 0)
				--timer_double_blink;
			if(timer_double_blink == 0)
			{
				timer_double_blink = 500;
				led_high('A',GPIO_LED);
				led_state = LED_IDLE;
			}
			break;
	}
}
#endif

#if (LED_STATEMACHINLE_IMPLEMENT_METHOD == 0)
/***************************************************************************************
Func Name	: LED_StateMachine
Return 		: void
Parameters	: void
Descript	: Led State Machine Impletion 0 , logic as drawing below.
Developer	: Jack Kilby
Update		: 2019-01-16

					IDLE
	                / ^\
	  led_onoff==1 /   \\			-: timer_blink == 0
				  /    -\\+			+: timer_blink == 0 && led_blink = 1 && led_onoff = 0
                 v	     \v
				ON			BLINK			Priority 1: LED ON
											Priority 2:	LED BLINK
***************************************************************************************/
typedef enum
{
	LED_IDLE,
	LED_ON,
	LED_BLINK
}led_state_t;
led_state_t led_state = LED_IDLE;

uint32_t timer_blink = 0;
int led_onoff_flag = 0;
int led_blink_flag = 0;
void LED_StateMachine(void)
{
	switch(led_state)
	{
		case LED_IDLE:
			if(timer_blink > 0)
				--timer_blink;
			
			if(1 == led_onoff_flag)
			{
				led_low('A', GPIO_LED);
				led_state = LED_ON;
			}
			else if((0 == timer_blink) && (1 == led_blink_flag))
			{
				timer_blink = 20000;
				led_state = LED_BLINK;
			}

			if(LED_IDLE != led_state)
			{
				led_low('A', GPIO_LED);
			}
			break;
					
		case LED_ON:
			if(0 == led_onoff_flag)
			{
				led_state = LED_IDLE;
				led_high('A', GPIO_LED);
			}
			break;
		
		case LED_BLINK:
			if(timer_blink > 0)
				--timer_blink;
			else
			{
				led_high('A', GPIO_LED);
				timer_blink = 10000;
				led_state = LED_IDLE;
			}
	}
}
#elif(LED_STATEMACHINLE_IMPLEMENT_METHOD == 1)
/***************************************************************************************
Func Name	: LED_StateMachine
Return 		: void
Parameters	: void
Descript	: Led State Machine Impletion 1 , logic as drawing below.
Developer	: Jack Kilby
Update		: 2019-01-16

					 ON
	                /^ ^
				  -//   \				-: led_on_flag = 0
				  //+   +\ 				+: led_on_flag=1
                 v/blink=1\
				OFF<=====>BLINK			Priority 1: LED ON
				  blink!=1				Priority 2:	LED BLINK
***************************************************************************************/
typedef enum
{
	LED_OFF,
	LED_ON,
	LED_BLINK
}led_state_t;
led_state_t led_state = LED_OFF;

int led_on_flag = 0;
int led_blink_flag = 0;
void LED_StateMachine(void)
{
	switch(led_state)
		{
			case LED_OFF:
				if(1 == led_on_flag)
				{
					led_low('A',GPIO_LED);
					led_state = LED_ON;
				}
				else if (1 == led_blink_flag)
				{
					led_state = LED_BLINK;
				}
				break;
			
			case LED_ON:
				if(0 == led_on_flag )
				{
					led_high('A', GPIO_LED);
					led_state = LED_OFF;
				}
				break;
			
			case LED_BLINK:
				led_blink('A', GPIO_LED, 20000, 10000);
				if(1 == led_on_flag)
				{
					led_low('A',GPIO_LED);
					led_state = LED_ON;
				}
				else if(1 != led_blink_flag)
				{
					led_high('A', GPIO_LED);
					led_state = LED_OFF;
				}
				break;
			
			//I can still give another GPIO Blink state. FAST_BLINK, SLOW_BLINK ...
		}
}

/********************************************************************************
Func Name	: led_blink
Return 		: void
Parameters	: char port: GPIOA as 'A', GPIOB as 'B'...
			  int  pin : the pin number under the port.
	 int onTimeInterval: LED_ON time interval when blink
	int offTimeInterval: LED_OFF time interval when blink
Descript	: Let LED blink or a gpio high and low alternately.
Developer	: Jack Kilby
Update		: 2019-01-16
********************************************************************************/
typedef enum
{
	LED_BLINK_ON,
	LED_BLINK_OFF
}led_blink_state_t;
led_blink_state_t led_blink_state = LED_BLINK_ON;
uint32_t blink_timer=0;
void led_blink(char port, int pin, int onTimeInterval, int offTimeInterval)
{
	++blink_timer;
	switch (led_blink_state)
	{
		case LED_BLINK_OFF:
			if(blink_timer > offTimeInterval)
			{
				led_low(port, pin);
				led_blink_state = LED_BLINK_ON;
				blink_timer = 0;
			}
			break;
		
		case LED_BLINK_ON:
			if(blink_timer > onTimeInterval)
			{
				led_high(port, pin);
				led_blink_state = LED_BLINK_OFF;
				blink_timer = 0;
			}
			break;
	}
}
#endif

