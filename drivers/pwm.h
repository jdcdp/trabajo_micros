//AUTHOR: Jaime de Castro 14708
//PWM code
#ifndef _PWM_H_
#define _PWM_H_
#include "pwm.c"
#include "pinout.h"

#define PWM_MAX      0xFFFF

void init_pwm();

void pwm(uint8_t motnum, uint8_t speed);

#endif
