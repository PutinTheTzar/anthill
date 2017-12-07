#include "urv_time.h"

uint64_t urv_time_us()
{	
	uint64_t time_l, time_h;
	__asm__ (
      "csrr t0, time \n\t"
	  "sw t0, %0 \n\t"
      : "=m" (time_l)
	);
	__asm__ (
      "csrr t0, timeh \n\t"
	  "sw t0, %0 \n\t"
      : "=m" (time_h)
	);
    return (time_l | (time_h << 32));
}

void urv_sleep_us(uint64_t timeout)
{	
	uint64_t start_time = urv_time_us();
	while( (urv_time_us() - start_time) < timeout );
}