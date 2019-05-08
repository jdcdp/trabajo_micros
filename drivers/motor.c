//AUTHOR: Jaime de Castro 14708
//Motor control
#include "motor.h"


void motor_init(){
  cli();
  DDRB=0xFF;
  ENDSTOPDDR=0;
  OPTENDDDR&=~(1<<0|1<<1);
  endstop_state=ENDSTOPS;//compare variable for pcint change detection
  pwm_init();
  sei();
}

void update_pwm(){
  int i;
  for(i=0;i<4;i++){
    if(motor[i].en){
      switch(i){
	case M1: bitchange(MOTOR_DIR_PORT,M1_DIR,motor[i].dir);
        case M2: bitchange(MOTOR_DIR_PORT,M2_DIR,motor[i].dir);
        case M3: bitchange(MOTOR_DIR_PORT,M3_DIR,motor[i].dir);
      }
      pwm(i,motor[i].spd);
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

  if (motor[motnum].en){
    motor[motnum].spd=spd;
    update_pwm();
    return 0;
  }
  else {
    //PRINT ERROR: MOTOR DISABLED
    return 1;
  }
}

void disableMotor(uint8_t motnum){
  motor[motnum].en=0;
  motor[motnum].spd=0;
  update_pwm();
}

void disableAllMotors(){
  disableMotor(M1);
  disableMotor(M2);
  disableMotor(M3);
  disableMotor(M4);
}
void enableMotor(uint8_t motnum){
  motor[motnum].en=1;
  update_pwm();
}

void setDir(uint8_t motnum, uint8_t direction){
  if(direction){
    motor[motnum].dir=1;
  }
  else{
    motor[motnum].dir=0;
  }
  update_pwm();
}

void setPos(uint8_t motnum, uint16_t wpos){
  motor[motnum].pos=wpos;
}

void setWantedPos(uint8_t motnum, uint16_t wpos){
  motor[motnum].fpos=wpos;
}

uint16_t getPos(uint8_t motnum){
  return motor[motnum].pos;
}

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
}


ISR(ENDSTOP_INTERRUPT){

//TO DO:Set interrupt mask to disable bounces


  /*read all pin changes but rise on 6 and 7*/
  switch(ENDSTOPS ^ endstop_state ^ (endstop_state & (1<<6 | 1<<7))) {

		case 1<<0: ISR_SW1();PORTB=0x01;

        case 1<<1: ISR_SW2();

        case 1<<2: ISR_SW3();

        case 1<<3: ISR_SW4();

        case 1<<4: ISR_SW5();

        case 1<<5: ISR_SW6();

        case 1<<6: ISR_SW7(); delay(10);//!Bounces

        case 1<<7: ISR_SW8(); delay(10);//!Bounces

	//default: PRINT(PCINT ERROR)
  }

  endstop_state=ENDSTOPS;

    //Reenable interrupt
}


void ISR_SW1(){ //Endstop M1_HIGH
  disableMotor(M1);
  setDir(M1,DOWN);
}

void ISR_SW2(){//Endstop M1_LOW
  disableMotor(M1);
  setDir(M1,UP);
  setPos(M1,0);
}

void ISR_SW3(){//Endstop M2_HIGH
  disableMotor(M2);
  setDir(M2,DOWN);
}

void ISR_SW4(){//Endstop M2_LOW
  disableMotor(M2);
  setDir(M2,UP);
  setPos(M2,0);
}

void ISR_SW5(){//Endstop M3_RIGHT
  disableMotor(M3);
  setDir(M3,LEFT);
  setPos(M3,0);
}

void ISR_SW6(){//Endstop M3_LEFT
  disableMotor(M3);
  setDir(M3,LEFT);
}

void ISR_SW7(){//Position detector M3
  if(motor[M3].dir==LEFT){
    motor[M3].pos++;
    if(motor[M3].pos==motor[M3].fpos) {
    	if(motor[M3].spd==SLOW_CONTACT) {
		disableMotor(M3);
	}
	else {
    		delay(TOUCH_DELAY);
    		setSpeed(M3,SLOW_CONTACT);
    		setDir(M3,RIGHT);
	}
    }
  }
  else{
    motor[M3].pos--;
    if(motor[M3].pos==motor[M3].fpos-1) {
       if(motor[M3].spd==SLOW_CONTACT) {
                disableMotor(M3);
        }
        else {
                delay(TOUCH_DELAY);
                setSpeed(M3,SLOW_CONTACT);
                setDir(M3,LEFT);
        }
    }
  }
}

void ISR_SW8(){ //M4 step counter
  motor[M4].pos++;
  if (motor[M4].pos==YTURNCOUNT){
  	motor[M4].pos=0;
#ifdef _SYS_CALL_
	syscall_product_out();    //for detecting missing products
#endif
  }
}

ISR(SO3){//Optical Encoder M1
  if(motor[M1].dir==UP){
    motor[M1].pos++;
  }
  else{
    motor[M1].pos--;
  }
#ifdef _LIB_CALL_
  motorZroutine();
  libcall_motorsync();
#endif
}

ISR(SO4){//Optical Encoder M2
  if(motor[M2].dir==UP){
    motor[M2].pos++;
  }
  else{
    motor[M2].pos--;
  }
  motorZroutine();
#ifdef _LIB_CALL_
  motorZroutine();
  libcall_motorsync();
#endif

}



//ISR(SW10) Not needed, level sensors
//ISR(SW11)
