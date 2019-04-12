//AUTHOR: Jaime de Castro 14708

#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>
#include "pinout.h"

#define M1 0
#define M2 1
#define M3 2
#define M4 3
#define MAX 255
#define UP 1
#define DOWN 0
#define RIGHT 0
#define LEFT 1

#define MAXSPEEDM1 255
#define MAXSPEEDM2 255
#define MAXSPEEDM3 255
#define MAXSPEEDM4 255

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


typedef struct motor {
uint8_t dir=1;
uint8_t spd=0;
uint8_t en=0;
uint16_t pos;
uint16_t fpos;
} motor[4];

void disableMotor(uint8_t motnum);

void enableMotor(uint8_t motnum);

uint8_t setSpeed(uint8_t motnum,uint8_t spd);

void setDir(uint8_t motnum,uint8_t direction);

void setWantedPos(uint16_t wpos, uint8_t motnum);

void getPos(uint8_t motnum);


ISR(SW1);
ISR(SW2);
ISR(SW3);
ISR(SW4);
ISR(SW5);
ISR(SW6);
ISR(SW7);
ISR(S03);
ISR(S04);


#endif
