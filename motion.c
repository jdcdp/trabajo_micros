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


/*	Demasiado intensivo, medir solo uno de los encoders
void motorZroutine(){
 int16_t d1,d2;
 d1=abs(motor[M1].fpos-motor[M1].pos);
 d2=abs(motor[M2].fpos-motor[M2].pos);
 if(min(d1,d2)<ZALIGNSTOP){
 disableMotor(M1);
 disableMotor(M2);
 enableMotor(M3);
 }
 else if (min(d1,d2)<ZALIGNSLOW){
 setSpeed(M1,ZALIGNSPEED);
 setSpeed(M2,ZALIGNSPEED);
 }
}*/


void libcall_motorZroutine(){
 int16_t d;
 d=abs(motor[M1].fpos-motor[M1].pos);
 if(d<ZALIGNSTOP){
 disableMotor(M1);
 disableMotor(M2);
 enableMotor(M3);
 unblock();
 }
 else if (d<ZALIGNSLOW){
 setSpeed(M1,ZALIGNSPEED);
 setSpeed(M2,ZALIGNSPEED);
 }
}


void unblock(){
	is_blocked=0;
}

void block(){
	is_blocked=1;
	sei();
	while(is_blocked){}
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
#ifdef _LIB_CALL_
  block();
#endif
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
#ifdef 	_LIB_CALL_
  block();
#endif
}



void moveZ(uint16_t position){
  setWantedPos(M1,position);
  setWantedPos(M2,position);
  enableMotor(M1);
  enableMotor(M2);
#ifdef _LIB_CALL_
  block();
#endif
}

void moveX(uint8_t position){ 
  setWantedPos(M3,position);
  if(PIN_SW7==0 && getPos(M3)!=getWantedPos(M3)){
	setDir(M3,((getPos(M3)<position) ^ RIGHT));
    enableMotor(M3);
    setSpeed(M3,MAXSPEED);
  }
#ifdef _LIB_CALL_
  block();
#endif
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
    case 1: moveZ(ENC2FLOOR3+ZOFFSET);	moveX(3); moveZ(ENC2FLOOR3);
    case 2: moveZ(ENC2FLOOR3+ZOFFSET);  moveX(2); moveZ(ENC2FLOOR3);
    case 3: moveZ(ENC2FLOOR3+ZOFFSET);  moveX(1); moveZ(ENC2FLOOR3);
    case 4: moveZ(ENC2FLOOR2+ZOFFSET);  moveX(3); moveZ(ENC2FLOOR2);
    case 5: moveZ(ENC2FLOOR2+ZOFFSET);  moveX(2); moveZ(ENC2FLOOR2);
    case 6: moveZ(ENC2FLOOR2+ZOFFSET);  moveX(1); moveZ(ENC2FLOOR2);
    case 7: moveZ(ENC2FLOOR1+ZOFFSET);  moveX(3); moveZ(ENC2FLOOR1);
    case 8: moveZ(ENC2FLOOR1+ZOFFSET);  moveX(2); moveZ(ENC2FLOOR1);
    case 9: moveZ(ENC2FLOOR1+ZOFFSET);  moveX(1); moveZ(ENC2FLOOR1);
  }
 #ifdef _SYS_CALL_
  syscall_aligned();
 #endif
}

