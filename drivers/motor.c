//AUTHOR: Jaime de Castro 14708

#include "motor.h"



uint8_t setSpeed(uint8_t motnum,uint8_t spd){

  if(motor[motnum].en){
    speed[motor]=spd;
    pwm();
    return 0;
  }
  else return 1;
}

void disableMotor(uint8_t motnum){
  motor[motnum].en=0;
//  motor[motnum].spd=0;//es necesario?
  pwm();
}

void enableMotor(uint8_t motnum){
  motor[motnum].en=1;
}

void setDir(uint8_t motnum, uint8_t direction){
  if(direction){
    motor[motnum].dir=1;
  }
  else {
     motor[motnum].dir=0;
  }
}
void setWantedPos(uint16_t wpos, uint8_t motnum){
  motor[motnum].fpos=wpos;
}

uint16_t getPos(uint8_t motnum){
  return motor[motnum].pos;
}



ISR(SW1){
  disableMotor(M1)
  setDir(M1,DOWN)
  }

ISR(SW2){
  disableMotor(M1)
  setDir(M1,UP)
  setPos(M1,0)
  }

ISR(SW3){  disableMotor(M2)
  setDir(M2,DOWN)
  }

ISR(SW4){
  disableMotor(M2)
  setDir(M2,UP)
  setPos(M2,0)
  }

ISR(SW5){
  disableMotor(M3)
  setDir(M3,LEFT)
  setPos(M3,0)
  }

ISR(SW6){ //fin de carrera
  disableMotor(M3)
  setDir(M3,LEFT)
  }

ISR(SO3){ //encoder1
//codigo antirrebotes
  if(motor[M1].dir==UP){
    motor[M1].pos++;
  }
  else{
    motor[M1].pos--;
  }

ISR(SO4){  //encoder 2
//codigo antirrebotes
  if(motor[M2].dir==UP){
    motor[M2].pos++;
  }
  else{
    motor[M2].pos--;
  }
}

ISR(SW7){ //cuentapasos motor X
//codigo antirrebotes
  if(motor[M3].dir==LEFT){
    motor[M3].pos++;
  }
  else{
    motor[M3].pos--;
  }
  if(motor[M3].pos==motor[M3].fpos){
    touch_pos();
  }
}


/*
ISR(SW10) sensores de nivel
ISR(SW11)
ISR(SW8) sensor pasos M4, no me hace falta
*/
