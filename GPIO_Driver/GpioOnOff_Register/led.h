#include <stm32f0xx.h>

#define GPIO_LED	4

void led_high(char port, int pin);
void led_low(char port, int pin);
void LED_StateMachine(void);
void led_blink(char port, int pin, int onTimeInterval, int offTimeInterval);
