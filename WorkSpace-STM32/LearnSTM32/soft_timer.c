#include "soft_timer.h"
#include "sys_timer.h"

#define SOFT_TIMER_STATE_STOPED							(0)
#define SOFT_TIMER_STATE_START							(1)
#define SOFT_TIMER_STATE_REACHED						(2)


void soft_timer_stop (soft_timer_t * timer)
{
	timer->state = SOFT_TIMER_STATE_STOPED;
}

void soft_timer_set_start_point (soft_timer_t * timer)
{
	timer->start = get_current_time();
}

void soft_timer_set_timeout (soft_timer_t *timer, uint32_t timeout_ms)
{
	timer->stop = timer->start + timeout_ms;
	timer->state = SOFT_TIMER_STATE_START;
}

bool soft_timer_is_timeout (soft_timer_t *timer)
{
	if(timer->state == SOFT_TIMER_STATE_STOPED)
	return false;

	if(timer->state == SOFT_TIMER_STATE_REACHED)
	return true;

	uint32_t current = get_current_time();

	if(timer->start < timer->stop)
	{
		if((current < timer->start) || (current >= timer->stop))
		{
			timer->state = SOFT_TIMER_STATE_REACHED;
			return true;
		}
	}
	else
	{
		if((current < timer->start) && (current >= timer->stop))
		{
			timer->state = SOFT_TIMER_STATE_REACHED;
			return true;
		}
	}

	return false;
}
