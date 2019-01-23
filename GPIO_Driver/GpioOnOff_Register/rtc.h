#ifndef _RTC_H_
#define _RTC_H_

#include <stm32f0xx.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	uint32_t time_start;
	uint32_t interval;
	uint32_t time_end;
}rtc_timer_t;


void rtc_add_timer(rtc_timer_t * timer, uint32_t interval);
bool rtc_is_timer_hit(rtc_timer_t * timer);
uint32_t rtc_get_time(void);


#endif
