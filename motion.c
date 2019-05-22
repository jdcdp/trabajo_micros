//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#include "motion.h"
#include "drivers/motor.h"


void setup_motion(){

        motor_init();
        //homeAll();
}


#define _LIB_CALL_
#ifdef  _LIB_CALL_

void libcall_motorsync(){
 /* if(motor[M1].dir==UP){
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
  }*/
}



int32_t debug1;
int32_t debug2;

void libcall_motorZroutine(){
   int32_t d,d1,d2;
   d1=abs((int32_t)motor[M1].fpos-(int32_t)motor[M1].pos);
   d2=abs((int32_t)motor[M1].fpos-(int32_t)motor[M1].pos);
   if(d1<0){d1=-d1;}
   if(d2<0){d2=-d2;}
   debug1=d1;
   debug2=d2;
   d=min(d1,d2);
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


void homeAll(){

	homeX();
	homeZ();
}

void homeX(){
  if((ENDSTOPS & (1<<SW5))==0){ //If the motor is not already in home position

	setDir(M3,RIGHT);
	enableMotor(M3);
	setSpeed(M3, MAXSPEED);
	delay(5);
	block();
 
  }
}

void homeZ(){
	int blks=0;
  if((ENDSTOPS & (1<<SW2))==0){
	//motor[M1].pos=888;
	setDir(M1,DOWN);
	enableMotor(M1);
	setSpeed(M1, MAXSPEED);
	blks++;

  }

  if((ENDSTOPS & (1<<SW4))==0){

	//motor[M2].pos=888;
	setDir(M2,DOWN);
	enableMotor(M2);
	setSpeed(M2, MAXSPEED);
	blks++;
  
  }
  while(blks--){
	  block();
  }

}



void moveZ(uint16_t position){


  setDir(M1,((getPos(M1)<position)?UP:DOWN));
  setDir(M2,((getPos(M2)<position)?UP:DOWN));
  setWantedPos(M1,position);
  setWantedPos(M2,position);
  enableMotor(M1);
  enableMotor(M2);
  setSpeed(M1,MAXSPEED);
  setSpeed(M2,MAXSPEED);
  block();


}

void moveX(uint8_t position){

    setDir(M3,LEFT);
    setWantedPos(M3,position);
    enableMotor(M3);
    setSpeed(M3,MAXSPEED);
	block();
  
}


void moveY(){
  enableMotor(M4);
  setSpeed(M4,MAXSPEED);
}

void stopY(){
  disableMotor(M4);
  motor[M4].pos=0;
  homeAll();
}



void selectProduct(uint8_t num){
//product to axes table
//	1 2 3
//	4 5 6
//	7 8 9

  disableAllMotors();
  homeX();
  switch(num){

	case 1: moveZ(ENC2FLOOR3+ZOFFSET);  moveX(3); moveZ(ENC2FLOOR3); break;
	case 2: moveZ(ENC2FLOOR3+ZOFFSET);  moveX(2); moveZ(ENC2FLOOR3); break;
	case 3: moveZ(ENC2FLOOR3+ZOFFSET);  moveX(1); moveZ(ENC2FLOOR3); break;
	case 4: moveZ(ENC2FLOOR2+ZOFFSET);  moveX(3); moveZ(ENC2FLOOR2); break;
	case 5: moveZ(ENC2FLOOR2+ZOFFSET);  moveX(2); moveZ(ENC2FLOOR2); break;
	case 6: moveZ(ENC2FLOOR2+ZOFFSET);  moveX(1); moveZ(ENC2FLOOR2); break;
	case 7: moveZ(ENC2FLOOR1+ZOFFSET);  moveX(3); moveZ(ENC2FLOOR1); break;
	case 8: moveZ(ENC2FLOOR1+ZOFFSET);  moveX(2); moveZ(ENC2FLOOR1); break;
	case 9: moveZ(ENC2FLOOR1+ZOFFSET);  moveX(1); moveZ(ENC2FLOOR1); break;
  }

 #ifdef _SYS_CALL_
  syscall_aligned();
 #endif
}

