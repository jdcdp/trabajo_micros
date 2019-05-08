//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#include "motion.h"
#include "drivers/motor.h"

#ifdef  _LIB_CALL_

void libcall_motorsync(){
	int16_t delta;
	delta=(getPos(M1)-getPos(M2));
	if (delta>MAXDELTA){
		setSpeed(M1,motor[M2].spd*MAXDELTA/abs(delta)); //Check how it behaves
	}
	else if (delta<-MAXDELTA){
		setSpeed(M2,motor[M1].spd*MAXDELTA/abs(delta));
	}
	else {
		setSpeed(M1,max(motor[M1].spd,motor[M2].spd));
	      	setSpeed(M2,max(motor[M1].spd,motor[M2].spd));
	}
}

#endif



void motion_init(){
motor_init();
homeAll();
}

void homeAll(){
  homeX();
  homeZ();
}

void homeX(){
  setDir(M3,RIGHT);
  setWantedPos(M3,0);
  setSpeed(M3, MAXSPEED);
  enableMotor(M3);
}

void homeZ(){
  setDir(M1, UP);
  setSpeed(M1, MAXSPEED);
  setDir(M2, UP);
  setSpeed(M2, MAXSPEED);
  setWantedPos(M1,0);
  setWantedPos(M2,0);
  enableMotor(M1);
  
  enableMotor(M2);
}



void moveZ(uint16_t position){
  setWantedPos(M1,position);
  setWantedPos(M2,position);
  enableMotor(M1);
  enableMotor(M2);
}

void moveX(uint8_t position){ //Comprobar esta funcion
  setWantedPos(M3,position);
  setDir(M3,(getPos(M3)<position));
  if(getPos(M3)!=position){
    enableMotor(M3);
    setSpeed(M3,MAXSPEED);
  }
  /*else{ //check sensor before moving
    enableMotor(M3);
    setSpeed(M3,SLOW_CONTACT);
  }*/
}


void moveY(){
  setDir(M4,UP);
  enableMotor(M4);
  setSpeed(M4,MAXSPEED);
}

void stopY(){
  disableMotor(M4);
}


uint8_t getState(){
  return 0;
}


void selectProduct(uint8_t num){
//product to axes table
//	1 2 3
//	4 5 6
//	7 8 9

  disableAllMotors();
  homeX();
  switch(num){
    case 1: moveZ(ENC2FLOOR3);	setWantedPos(M3,3);
    case 2: moveZ(ENC2FLOOR3);  setWantedPos(M3,2);
    case 3: moveZ(ENC2FLOOR3);  setWantedPos(M3,1);
    case 4: moveZ(ENC2FLOOR2);  setWantedPos(M3,3);
    case 5: moveZ(ENC2FLOOR2);  setWantedPos(M3,2);
    case 6: moveZ(ENC2FLOOR2);  setWantedPos(M3,1);
    case 7: moveZ(ENC2FLOOR1);  setWantedPos(M3,3);
    case 8: moveZ(ENC2FLOOR1);  setWantedPos(M3,2);
    case 9: moveZ(ENC2FLOOR1);  setWantedPos(M3,1);
  }
}

