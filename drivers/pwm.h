//AUTHOR: Jaime de Castro 14708
//PWM code
#ifndef _PWM_H_
#define _PWM_H_

#include <stdint.h>
#include <avr/io.h>
#include "../pinout.h"
#include "motor.h"

#define PWM_MAX      0xFFFF

void pwm_init();

void pwm(uint8_t motnum, uint8_t speed);

#endif
