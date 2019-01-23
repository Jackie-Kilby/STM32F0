#include "rtc.h"

uint32_t rtc_time;

void rtc_add_timer(rtc_timer_t * timer, uint32_t interval)
{
	timer->time_start = rtc_time;
	timer->interval = interval;
	timer->time_end = timer->time_start+interval;
}

bool rtc_is_timer_hit(rtc_timer_t * timer)
{
	if(timer->time_end < rtc_time)
	{
		return true;
	}
	else
	{
		return false;
	}
}

uint32_t rtc_get_time(void)
{
	while(!((RTC->ISR & RTC_ISR_RSF) == RTC_ISR_RSF));
	uint32_t current_time = 10*((RTC->TR & (RTC_TR_ST_Msk)) >> RTC_TR_ST_Pos) + ((RTC->TR & (RTC_TR_SU_Msk)) >> RTC_TR_SU_Pos);
	current_time += 60 * (10*((RTC->TR & (RTC_TR_MNT_Msk)) >> RTC_TR_MNT_Pos) + ((RTC->TR & (RTC_TR_MNU_Msk)) >> RTC_TR_MNU_Pos));
	if((RTC->TR & (RTC_TR_HT_Msk)) || (RTC->TR & (RTC_TR_HU_Msk)))
	{
		current_time += 3600 * (10*((RTC->TR & (RTC_TR_HT_Msk)) >> RTC_TR_HT_Pos) + ((RTC->TR & (RTC_TR_HU_Msk)) >> RTC_TR_HU_Pos));
	}
	return current_time;
}


