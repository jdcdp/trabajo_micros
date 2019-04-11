//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#ifndef _MOTION_H_
#define _MOTION_H_

#include <stdint.h>
#include "driver/motor.h"

uint8_t homeZ();

uint8_t getState();

uint8_t sendPos(uint8_t num);

uint8_t releaseProduct(uint8_t num);

#endif




//definiciones


