//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#include "motion.h"

uint8_t init(){
//set interrupts:
//-level sensor
//-optical endstops
motorSetup();
homeAll();
return 0;
}

void homeAll(){
  homeZ();
  homeX();
}

void homeX(){
  setDir(M3,RIGHT);
  SetSpeed(M3, 0.5*MAXSPEED);
  enableMotor(M3);
}

void homeZ(){
  setDir(M1, UP);
  setSpeed(M1, 0.5*MAXSPEED);
  setDir(M2, UP);
  setSpeed(M2, 0.5*MAXSPEED);
  enableMotor(M1);
  enableMotor(M2);
}



void moveZ(uint16_t position){
  setWantedPos(M1,position);
  setWantedPos(M2,position);
  enableMotor(M1);
  enableMotor(M2);
}

void moveX(uint8_t position){ //REVISAR ESTA FUNCION
  setWantedPos(M3,position);
  tpos=getpos();
  if(tpos!=position){
    setDir(M3,(getPos(M3)>tpos))//check this direction
    enableMotor(M3);
    setSpeed(M3,0.5*MAXSPEED)
  }
}


void moveY(){
  setDir(M4,UP);//check this direction
  enableMotor(M4);
  setSpeed(M4,MAXSPEED);
}

void stopY(){
  disableMotor(M4)
}


uint8_t getState(){

}


void releaseProduct(uint8_t num){
//product to axes table

}

