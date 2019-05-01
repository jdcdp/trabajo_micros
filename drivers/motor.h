//AUTHOR: Jaime de Castro 14708
//Motor control
#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>
#include "../pinout.h"

#define M1 0
#define M2 1
#define M3 2
#define M4 3
#define UP 1
#define DOWN 0
#define RIGHT 0
#define LEFT 1

#define MAXSPEED 0xFFFF

#define TOUCH_DELAY 300 /*Delay in ms to move around M3's trigger point*/
#define SLOW_CONTACT 20 /*Slow speed (up to 255) for M3 alignment*/


/* Not used yet
#define INVMOTORM1 0
#define INVMOTORM2 0
#define INVMOTORM3 0
#define INVMOTORM4 0

#define BRAKEFEATUREM1 0
#define BRAKEFEATUREM2 0
#define BRAKEFEATUREM3 0
#define BRAKEFEATUREM4 0
*/

//Variables and types

typedef struct motor {
uint8_t dir=1;
uint16_t spd=0;
uint8_t en=0;
uint16_t pos;
uint16_t fpos;
} motor[4];

uint16_t endstop_state=0;


//Functions

void motorSetup();

void disableMotor(uint8_t motnum);

void enableMotor(uint8_t motnum);

uint8_t setSpeed(uint8_t motnum,uint16_t spd);

void setDir(uint8_t motnum,uint8_t direction);

void setWantedPos(uint16_t wpos, uint8_t motnum);

void getPos(uint8_t motnum);

void update_pwm();

ISR_SW1();

ISR_SW2();

ISR_SW3();

ISR_SW4();

ISR_SW5();

ISR_SW6();

ISR_SW7();

ISR_SW8();

ISR_SO3();

ISR_SO4();

#endif
