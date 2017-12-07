
#ifndef __SYS_TIMER_C_H
#define __SYS_TIMER_C_H

#include <stdint.h>

/* function declaration*/
uint64_t urv_time_us();
void     urv_sleep_us(uint64_t timeout);

#endif
