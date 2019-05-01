//AUTHOR: Jaime de Castro 14708
//Motor control
#include "motor.h"


void motorSetup(){
cli();
ENDSTOPDDR=0;
endstop_state=ENDSTOPS;//compare variable for pcint change detection
sei();
}




void update_pwm(){
  for(i=0;i<4;i++){
    if(motor[i].en){
      switch(i)
	case M1: M1DIR=motor[i].dir;
	case M2: M2DIR=motor[i].dir;
	case M3: M3DIR=motor[i].dir;
	case M4: M4DIR=motor[i].dir;
        pwm(i,motor[i].spd);//deberia funcionar
	//PORTB|=0b1000000>>i; //BYPASS TEMPORAL AL PWM
	//More to do...?
    }
    else{
      pwm(i,0);
    }
  }
}

uint8_t setSpeed(uint8_t motnum,uint16_t spd){

  if (spd>MAXSPEED) {
    spd=MAXSPEED;
  }

  if(motor[motnum].en){
    motor[motnum].spd=spd;
    update_pwm();
    return 0;
  }
  else {
    //PRINT ERROR: MOTOR DISABLED
    return 1;
}

void disableMotor(uint8_t motnum){
  motor[motnum].en=0;
  motor[motnum].spd=0;
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
  update_pwm();
}

void setWantedPos(uint16_t wpos, uint8_t motnum){
  motor[motnum].fpos=wpos;
}

uint16_t getPos(uint8_t motnum){
  return motor[motnum].pos;
}



ISR(ENDSTOP_INTERRUPT){

//Set interrupt mask to disable bounces

uint8_t temp;

switch(ENDSTOPS ^ endstop_state){

	case 1: ISR_SW1;

        case 2: ISR_SW2;

        case 3: ISR_SW3;

        case 1: ISR_SW4;

        case 1: ISR_SW5;

        case 1: ISR_SW6;

        case 1: ISR_SW7;

        case 1: ISR_SW8;

        case 1: ISR_SO3;

        case 1: ISR_SO4;

	//default: PRINT(PCINT ERROR)
}

endstop_state=ENDSTOPS;

delay(10);

//Reenable interrupt
}


ISR_SW1(){ //Endstop M1_HIGH
  disableMotor(M1);
  setDir(M1,DOWN);
}

ISR_SW2(){//Endstop M1_LOW
  disableMotor(M1);
  setDir(M1,UP);
  setPos(M1,0);
}

ISR_SW3(){//Endstop M2_HIGH
  disableMotor(M2);
  setDir(M2,DOWN);
}

ISR_SW4(){//Endstop M2_LOW
  disableMotor(M2);
  setDir(M2,UP);
  setPos(M2,0);
}

ISR_SW5(){//Endstop M3_RIGHT
  disableMotor(M3);
  setDir(M3,LEFT);
  setPos(M3,0);
}

ISR_SW6(){//Endstop M3_LEFT
  disableMotor(M3)
  setDir(M3,LEFT)
}

ISR_SO3(){//Optical Encoder M1
  if(motor[M1].dir==UP){
    motor[M1].pos++;
  }
  else{
    motor[M1].pos--;
  }
  update_pwm();
}

ISR_SO4(){//Optical Encoder M2
  if(motor[M2].dir==UP){
    motor[M2].pos++;
  }
  else{
    motor[M2].pos--;
  }
  update_pwm();
}

ISR_SW7(){//Position detector M3             //NO TERMINADA

  if((motor[M3].pos==motor[M3].fpos) && (motor[M3].dir==LEFT)){
    //if slow...
    delay(TOUCH_DELAY);
    setSpeed(M3,SLOW_CONTACT);
    setDir(M3,RIGHT);

  }

  if(motor[M3].dir==LEFT){
    motor[M3].pos++;
    if(motor[M3].pos==motor[M3].fpos) {
    	if(motor[M3].speed==SLOW_CONTACT) {
		disableMotor(M3);
	}
	else {
    		delay(TOUCH_DELAY);
    		setSpeed(M3,SLOW_CONTACT);
    		setDir(M3,RIGHT);
	}


  }
  else{
    motor[M3].pos--;
  }
}
*/
/*
ISR(SW10) Level Sensors , I don't need them
ISR(SW11)
ISR(SW8) Quarter step M4, I don't need it. Maybe add if there are enough pins
*/
