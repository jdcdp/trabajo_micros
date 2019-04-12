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

void homeX(){
  setDir(M3,RIGHT);
  SetSpeed(M3, 0.5*MAXX);
  enableMotor(M3);
}

void homeZ(){
  setDir(M1, UP);
  setSpeed(M1, 0.5*MAXZ);
  setDir(M2, UP);
  setSpeed(M2, 0.5*MAXZ);
  enableMotor(M1);
  enableMotor(M2);
}



void moveZ(uint16_t position){
  setWantedPos(M1,position);
  setWantedPos(M2,position);
}

void moveX(uint8_t position){
  setWantedPos(M3,position);
  if(getPos()>position)
  setDir(M3,(getPos(M3)>))

}


void moveY(){
  setDir(M4,UP);
  enableMotor(M4);
  setSpeed(M4,MAXY);
}

void stopY(){
  disableMotor(M3)
}


uint8_t getState(){
}


void releaseProduct(uint8_t num){

}

