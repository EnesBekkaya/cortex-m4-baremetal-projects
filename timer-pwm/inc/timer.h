#ifndef INC_TIMER_H
#define INC_TIMER_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>


void timer_setup(void);
void timer_pwm_set_duty_cycle(float duty_cycle);
#endif