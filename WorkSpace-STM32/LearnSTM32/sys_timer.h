#ifndef SYS_TIMER_H_
#define SYS_TIMER_H_

#include "compile.h"


/* This function returns current time counter value.
 *
 */
extern uint32_t get_current_time (void);

/* This function configures the RTT as system timer.
 *
 */
extern void sys_timer_init (void);

#endif /* SYS_TIMER_H_ */
