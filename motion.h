//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#ifndef _MOTION_H_
#define _MOTION_H_

#include "macros.h"
#include "drivers/motor.h"
#include <stdint.h>

#define ENC1FLOOR1 18 //Z encoder floor levels
#define ENC1FLOOR2 107
#define ENC1FLOOR3 170
#define ENC2FLOOR1 30
#define ENC2FLOOR2 95
#define ENC2FLOOR3 150
#define ZOFFSET	   5  //Offset for x alignment

#define _LIB_CALL_
#ifdef 	_LIB_CALL_

#define MAXDELTA 10 //Minimum offset to start correction

#define _BLOCK_ //Whether movement instructions are simultaneous or consecutive


uint8_t is_blocked;

void block();

void unblock();

void libcall_motorsync();

void libcall_motorZroutine();

#endif

void setup_motion();

void homeAll();

void homeZ();

void homeX();

void moveZ(uint16_t position);

void moveX(uint8_t position);

void moveXY(uint8_t row, uint8_t col);

void moveY();

void stopY();

void selectProduct(uint8_t num);

#endif




