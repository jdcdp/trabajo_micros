//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#ifndef _MOTION_H_
#define _MOTION_H_

#include "drivers/motor.h"
#include <stdint.h>

#define ENC2FLOOR1 100 //encoder steps for floor level
#define ENC2FLOOR2 200
#define ENC2FLOOR3 300

void motion_init();

void homeAll();

void homeZ();

void homeX();

void moveZ(uint16_t position);

void moveX(uint8_t position);

void moveY();

void stopY();

uint8_t getState();//depende de la integracion

void selectProduct(uint8_t num);

#endif




