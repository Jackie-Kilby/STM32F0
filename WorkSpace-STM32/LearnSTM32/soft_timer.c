#include "compile.h"
#include "soft_timer.h"

#define SOFTTIMER_STATE_STOPPED	(0)
#define SOFTTIMER_STATE_RUNNING	(1)
#define SOFTTIMER_STATE_REACHED	(2)


void softtimer_stop(softtimer_t *timer)
{
	timer->state = SOFTTIMER_STATE_STOPPED;
}

void softtimer_set(softtimer_t *timer, uint32_t interval)
{
	timer->start_time = systimer_get_current();
	timer->end_time = timer->start_time + interval;
	timer->state = SOFTTIMER_STATE_RUNNING;
}

bool softtimer_is_hit(softtimer_t *timer)
{

	if(timer->state == SOFTTIMER_STATE_STOPPED)
	{
		return false;
	}
	if(timer->state == SOFTTIMER_STATE_REACHED)
	{
		return false;
	}

	uint32_t current_time = systimer_get_current();

	if(timer->start_time < timer->end_time)
	{
		if(timer->end_time < current_time || current_time < timer->start_time)
		{
			timer->state = SOFTTIMER_STATE_REACHED;
			return true;
		}
	}
	else
	{
		if(timer->end_time < current_time && current_time < timer->start_time)
		{
			timer->state = SOFTTIMER_STATE_REACHED;
			return true;
		}
	}
	return false;
}

