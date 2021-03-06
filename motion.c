//AUTHOR: Jaime de Castro 14708
//Codigo para el control del movimiento de los motores


#include "motion.h"
#include "drivers/motor.h"

#ifndef _LIB_CALL_
error
#endif

#ifndef _BLOCK_
error
#endif

#ifndef _SYS_CALL_
error
#endif



void setup_motion(){

        motor_init();
        homeAll();
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
	block();
  }
}

void homeZ(){

  uint8_t blks=0;
  if((ENDSTOPS & (1<<SW2))==0){  //If the motor is not already in home position
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
  #ifdef _BLOCK_
	block();
  #endif

}

void moveX(uint8_t position){

	setDir(M3,LEFT);
	setWantedPos(M3,position);
	enableMotor(M3);
	setSpeed(M3,MAXSPEED);
  #ifdef _BLOCK_
	block();
  #endif
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


#ifdef  _LIB_CALL_

void libcall_motorsync(){
 /* if(motor[M1].dir==UP){			// No es necesaria ya que los motores no tienen problemas de desalineación
	int16_t delta;
	delta=(getPos(M1)-getPos(M2));
	if (delta>MAXDELTA){
		setSpeed(M1,motor[M2].spd*MAXDELTA/ABS(delta)); 
	}
	else if (delta<-MAXDELTA){
		setSpeed(M2,motor[M1].spd*MAXDELTA/ABS(delta));
	}
	else {
		setSpeed(M1,max(motor[M1].spd,motor[M2].spd));
	      	setSpeed(M2,max(motor[M1].spd,motor[M2].spd));
	}
  }*/
}




void libcall_motorZroutine(){
   int32_t d,d1,d2;
   d1=ABS((int32_t)motor[M1].fpos-(int32_t)motor[M1].pos); //por alguna razon devuelven numeros negativos
   d2=ABS((int32_t)motor[M1].fpos-(int32_t)motor[M1].pos);
   if(d1<0){d1=-d1;}
   if(d2<0){d2=-d2;}
   d=min(d1,d2);
   if(d<ZALIGNSTOP){

	disableMotor(M1);
	disableMotor(M2);
	enableMotor(M3);
 #ifdef _BLOCK_
	unblock();
 #endif
}

   else if (d<ZALIGNSLOW){

	setSpeed(M1,ZALIGNSPEED);
	setSpeed(M2,ZALIGNSPEED);
   }
}
#endif


#ifdef _BLOCK_

void block(){            //funcion que para la ejecución del siguiente comando (sin ser bloqueante)
        is_blocked=1;    //para que las instrucciones sean consecutivas en lugar de simultáneas
	sei();
	while(is_blocked){}
}

void unblock(){
        is_blocked=0;
}

#endif

