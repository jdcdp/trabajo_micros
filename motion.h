//Codigo para el control de los motores


#ifndef _MOTION_H_
#define _MOTION_H_

#include <stdint.h>
#include "driver/motor.h"

uint8_t getState();

uint8_t sendPos(uint8_t num);

uint8_t releaseProduct(uint8_t num);

#endif




//definiciones


