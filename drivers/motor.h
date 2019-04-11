//AUTHOR: Jaime de Castro 14708

#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <stdint.h>
#include "time_m.h"
//#include "macros.h"
#include "pins.h"

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

#define INVMOTORM1 0
#define INVMOTORM2 0
#define INVMOTORM3 0
#define INVMOTORM4 0

#define BRAKEFEATUREM1 0
#define BRAKEFEATUREM2 0
#define BRAKEFEATUREM3 0
#define BRAKEFEATUREM4 0

typedef struct motor {
uint8_t dir=1;
uint8_t spd=0;
uint8_t en=0;
uint16_t pos;
} motor[4];

uint8_t setSpeed(uint8_t motor);

uint8_t setDir(uint8_t motor,);

#endif
