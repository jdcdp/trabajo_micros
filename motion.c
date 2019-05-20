//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#include "motion.h"
#include "drivers/motor.h"

#define _LIB_CALL_
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



void libcall_motorZroutine(){
 int16_t d;
 d=min(abs(motor[M1].fpos-motor[M1].pos),abs(motor[M2].fpos-motor[M2].pos));
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
//homeAll(); //#@#
}

void homeAll(){
  homeX();
  homeZ();
}

void homeX(){
  if((ENDSTOPS & (1<<SW5))==0){ //If the motor is not already in home position
     setDir(M3,RIGHT);
     enableMotor(M3);
     setSpeed(M3, MAXSPEED);
  }
#ifdef _LIB_CALL_
  block();
#endif
}

void homeZ(){
  if(((ENDSTOPS & (1<<SW2))==0) | ((ENDSTOPS & (1<<SW4))==0)){ //If some motor is not already homed
     setDir(M1,DOWN);
     setDir(M2,DOWN);
     enableMotor(M1);
     enableMotor(M2);
     setSpeed(M1, MAXSPEED);
     setSpeed(M2, MAXSPEED);
  }
#ifdef 	_LIB_CALL_
  block();
#endif
}



void moveZ(uint16_t position){
  
  setWantedPos(M1,position);
  setWantedPos(M2,position);
  enableMotor(M1);
  enableMotor(M2);
  setSpeed(M1,MAXSPEED);
  setSpeed(M2,MAXSPEED);
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

void moveXZ(uint8_t row,uint8_t col){
	
	if(row!=motor[M1].pos){
		
		moveZ(getPos(M1)+ZOFFSET);
		homeX();
		switch(row){
			case 1: moveZ(ENC2FLOOR3+ZOFFSET); break;
			case 2: moveZ(ENC2FLOOR2+ZOFFSET); break;
			case 3: moveZ(ENC2FLOOR1+ZOFFSET); break;
		}
		moveX(col);
		switch(row){
			case 1: moveZ(ENC2FLOOR3); break;
			case 2: moveZ(ENC2FLOOR2); break;
			case 3: moveZ(ENC2FLOOR1); break;
		}
	}
	else if(col!=getPos(M3)){
		
		moveZ(getPos(M1)+ZOFFSET);
		moveX(col);
		switch(row){
			case 1: moveZ(ENC2FLOOR3+ZOFFSET); break;
			case 2: moveZ(ENC2FLOOR2+ZOFFSET); break;
			case 3: moveZ(ENC2FLOOR1+ZOFFSET); break;
		}
	}
	
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
    case 1: moveXZ(3,3) break;
    case 2: moveXZ(3,2) break;
    case 3: moveXZ(3,1) break;
    case 4: moveXZ(2,3) break;
    case 5: moveXZ(2,2) break;
    case 6: moveXZ(2,1) break;
    case 7: moveXZ(1,3) break;
    case 8: moveXZ(1,2) break;
    case 9: moveXZ(1,1) break;
  }
 #ifdef _SYS_CALL_
  syscall_aligned();
 #endif
}

