//AUTHOR: Jaime de Castro 14708
//Motor control
#include "motor.h"

void update_pwm(){
  for(i=0;i<4;i++){
    if(motor[i].en){
      //what about direction
      pwm(i,motor[i].spd);
	//More to do...

    }
    else{
      

    }
  }
}

uint8_t setSpeed(uint8_t motnum,uint8_t spd){

  if(motor[motnum].en){
    speed[motor]=spd;
    update_pwm();
    return 0;
  }
  else return 1;
}

void disableMotor(uint8_t motnum){
  motor[motnum].en=0;
//  motor[motnum].spd=0;//es necesario?
  update_pwm();
}

void enableMotor(uint8_t motnum){
  motor[motnum].en=1;
  update_pwm();
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



ISR(SW1){ //Endstop M1_HIGH
  disableMotor(M1);
  setDir(M1,DOWN);
}

ISR(SW2){//Endstop M1_LOW
  disableMotor(M1);
  setDir(M1,UP);
  setPos(M1,0);
}

ISR(SW3){//Endstop M2_HIGH
  disableMotor(M2);
  setDir(M2,DOWN);
}

ISR(SW4){//Endstop M2_LOW
  disableMotor(M2);
  setDir(M2,UP);
  setPos(M2,0);
}

ISR(SW5){//Endstop M3_RIGHT
  disableMotor(M3);
  setDir(M3,LEFT);
  setPos(M3,0);
}

ISR(SW6){//Endstop M3_LEFT
  disableMotor(M3)
  setDir(M3,LEFT)
}

ISR(SO3){//Optical Encoder M1
//codigo antirrebotes
  if(motor[M1].dir==UP){
    motor[M1].pos++;
  }
  else{
    motor[M1].pos--;
  }
  update_pwm();
}

ISR(SO4){//Optical Encoder M2
//codigo antirrebotes
  if(motor[M2].dir==UP){
    motor[M2].pos++;
  }
  else{
    motor[M2].pos--;
  }
  update_pwm();
}

ISR(SW7){//Position detector M3
//codigo antirrebotes

  if((motor[M3].pos==motor[M3].fpos) && (motor[M3].dir==LEFT)){
    //if slow...
    delay(TOUCH_DELAY);
    setSpeed(M3,SLOW_CONTACT);
    setDir(M3,RIGHT);

  }

  if(motor[M3].dir==LEFT){
    motor[M3].pos++;
  }
  else{
    motor[M3].pos--;
  }
}


/*
ISR(SW10) Level Sensors , I don't need them
ISR(SW11)
ISR(SW8) Quarter step M4, I don't need it. Maybe add if there are enough pins
*/
