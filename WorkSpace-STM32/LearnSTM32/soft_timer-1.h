#include "compile.h"
#include "sys_timer.h"

typedef struct
{
	uint32_t start_time;
	uint32_t end_time;
	uint8_t state;
}softtimer_t;

void softtimer_set(softtimer_t *timer, uint32_t interval);
bool softtimer_is_hit(softtimer_t * timer);

