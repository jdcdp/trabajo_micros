//AUTHOR: Jaime de Castro 14708
//Motor control
#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>
#include <avr/interrupt.h>
#include "../macros.h"
#include "../pinout.h"
#include "pwm.h"
#include "time.h"
#include "../motion.h"

#define M1 	0
#define M2 	1
#define M3 	2
#define M4 	3
#define UP 	1
#define DOWN 	0
#define RIGHT	0
#define LEFT 	1

#define MAXSPEED 	0xFFFF //(0 to FFFF)

#define TOUCH_DELAY 	300 /*Delay in ms to move around M3's trigger point*/
#define SLOW_CONTACT 	0x2FFF /*Slow speed for M3 alignment*/

#define YTURNCOUNT	10 //number of steps to signal supposed product release

#define ZALIGNSLOW	5 //Z step offset to slow movement
#define ZALIGNSPEED	0xAFFF //Speed when slowing
#define ZALIGNSTOP	2 //Z step offset to stop movement

//Variables and types

struct motor {
  uint8_t dir;
  uint16_t spd;
  uint8_t en;
  uint16_t pos;
  uint16_t fpos;
} motor[4];

uint8_t endstop_state;


//Functions

void motor_init();

void disableMotor(uint8_t motnum);

void disableAllMotors();

void enableMotor(uint8_t motnum);

void setSpeed(uint8_t motnum,uint16_t spd);

void setDir(uint8_t motnum,uint8_t direction);

void setPos(uint8_t motnum, uint16_t wpos);

void setWantedPos(uint8_t motnum, uint16_t wpos);

uint16_t getPos(uint8_t motnum);

uint16_t getWantedPos(uint8_t motnum);

void update_pwm();

void ISR_SW1();

void ISR_SW2();

void ISR_SW3();

void ISR_SW4();

void ISR_SW5();

void ISR_SW6();

void ISR_SW7();

void ISR_SW8();

#endif
