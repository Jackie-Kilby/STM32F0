#ifndef _SYS_CLOCK_H_
#define _SYS_CLOCK_H_

#include "compile.h"

void sysclock_init_use_hsi(void);
void sysclock_init_use_hse(void);
void sysclock_init_use_pll(void);

#endif 
