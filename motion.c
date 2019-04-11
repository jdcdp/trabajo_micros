//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#include "motion.h"

uint8_t init(){
//set interrupts:
//-level sensor
//-optical endstops
}

void homeAll(){
homeZ();
homeX();
}

void homeZ(){
setDir(M1, UP);
setSpeed(M1, 0.5*MAXZ);
setDir(M2, UP);
setSpeed(M2, 0.5*MAXZ);
enableMotor(M1);
enableMotor(M2);
}

void homeX(){
setDir(M3,RIGHT);
SetSpeed(M3, 0.5*MAXX);
enableMotor(M3);
}



uint8_t moveZ(uint8)



uint8_t getState(){




}

uint8_t sendPos(uint8_t num){

}

uint8_t releaseProduct(uint8_t num){

}

