//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#ifndef _MOTION_H_
#define _MOTION_H_

#include <stdint.h>

void homeAll();

void homeZ();

void homeX();

void moveZ(uint16_t position);

void moveX(uint8_t position);

void moveY();

void stopY();

uint8_t getState();//depende de la integracion

void releaseProduct(uint8_t num);

#endif




