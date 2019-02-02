#ifndef SOFT_TIMER_H_
#define SOFT_TIMER_H_

#include "compile.h"

typedef struct
{
	uint32_t start;
	uint32_t stop;
	uint8_t state;
} soft_timer_t;

/* This function stops the behave a software timer. However it is still running.
 * Parameters:
 *     	timer      	: A pointer to a software timer variable.
 */
extern void soft_timer_stop (soft_timer_t * timer);

/* This function sets the start point of a software timer. Once this function is called,
 * the timer starts to run (not behave until called soft_timer_set_start_point() function).
 *
 * Parameters:
 *     	timer      	: A pointer to a software timer variable.
 *
 */
extern void soft_timer_set_start_point (soft_timer_t * timer);

/* This function configures the timeout period of a software timer.
 * Once this function is called, the timer starts to behave.
 *
 * Parameters:
 *    	timer      	: A pointer to a software timer variable.
 *     	timeout_ms 	: The timeout period in milliseconds. e.g. 2000 = 2s
 */
extern void soft_timer_set_timeout (soft_timer_t *timer, uint32_t timeout_ms);

/* This function checks if the timeout event of a software timer is occurred.
 *
 * Parameters:
 *     	timer      	: A pointer to a software timer variable.
 *
 *
 * Return:
 * 		true		: A timeout event has occurred.
 * 		false		: A timeout event has not occurred.
 *
 *
 * Example:
 * 		sys_timer_init();
 *
 * 		...
 *
 * 		soft_timer_t t0;
 *
 * 		soft_timer_set_start_point(&t0);
 * 		soft_timer_set_timeout(&t0, 1000);
 *
 * 		...
 *
 * 		if(soft_timer_is_timeout(&t0))
 * 		{
 * 			...
 * 		}
 *
 */
extern bool soft_timer_is_timeout (soft_timer_t *timer);

#endif
