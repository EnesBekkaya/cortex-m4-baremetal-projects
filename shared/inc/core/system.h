#ifndef INC_SYSTEM_H
#define INC_SYSTEM_H

#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>
#include <common-defines.h>

#define CPU_FREQ 	 (84000000)
#define SYSTICK_FREQ (1000)

void system_setup(void);
uint64_t system_get_ticks(void);

#endif 