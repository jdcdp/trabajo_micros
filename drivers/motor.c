
//AUTHOR: Jaime de Castro 14708
//Motor control

#include "avr/interrupt.h"
#include "motor.h"


#ifndef _LIB_CALL_
error
#endif

#ifndef _BLOCK_
error
#endif


void motor_init(){
  cli();

  //Set optical encoders' interrupts
  OPTENDDDR&=~(1<<0|1<<1);
  EICRA|=(1<<ISC10 | 1<<ISC11 | 1<<ISC00 | 1<<ISC01); //11=rising
  EIMSK|=(1<<INT1 | 1<<INT0);

  //Set endstops' interrupts
  ENDSTOPDDR=0;
  PCICR |= 0b00000100; //PCINT DEL PUERTO K
  PCMSK2 = 0b11111111; //Enable PCINT2
  endstop_state=ENDSTOPS;//compare variable for pcint change detection

  DIRDDR|=1<<DDL2 | 1<<DDL6 | 1<<DDL7;

  //Set pwm timers
  pwm_init();

  //set initial conditions
  setDir(M1,DOWN);
  setDir(M2,DOWN);
  setDir(M3,RIGHT);
  sei();
}

void update_pwm(){
  int i;
  for(i=0;i<4;i++){

	if(motor[i].en){

		pwm(i,motor[i].spd);
	}
	else{

		pwm(i,0);
	}
   }
}

void setSpeed(uint8_t motnum,uint16_t spd){

	motor[motnum].spd=spd;
	update_pwm();
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
	switch(motnum){
		case M1: bitchange(MOTOR_DIR_PORT,M1_DIR,motor[motnum].dir); break;
		case M2: bitchange(MOTOR_DIR_PORT,M2_DIR,motor[motnum].dir); break;
		case M3: bitchange(MOTOR_DIR_PORT,M3_DIR,motor[motnum].dir); break;
  }
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

uint16_t getWantedPos(uint8_t motnum){

	return motor[motnum].fpos;
}





ISR(ENDSTOP_INTERRUPT){

  //read all pin changes

  switch(ENDSTOPS ^ endstop_state) {

	case 1<<SW1: PCMSK2 &= ~1<<SW1; delay(3); if (ENDSTOPS & (1<<SW1)) {ISR_SW1();} break; //Only rise

	case 1<<SW2: PCMSK2 &= ~1<<SW2; delay(3); if (ENDSTOPS & (1<<SW2)) {ISR_SW2();} break;

	case 1<<SW3: PCMSK2 &= ~1<<SW3; delay(3); if (ENDSTOPS & (1<<SW3)) {ISR_SW3();} break;

	case 1<<SW4: PCMSK2 &= ~1<<SW4; delay(3); if (ENDSTOPS & (1<<SW4)) {ISR_SW4();} break;

	case 1<<SW5: PCMSK2 &= ~1<<SW5; delay(3); if (ENDSTOPS & (1<<SW5)) {ISR_SW5();} break;

	case 1<<SW6: PCMSK2 &= ~1<<SW6; delay(3); if (ENDSTOPS & (1<<SW6)) {ISR_SW6();} break;

	case 1<<SW7: PCMSK2 &= ~1<<SW7; delay(5); ISR_SW7();  break;//Rise and fall

	case 1<<SW8: PCMSK2 &= ~1<<SW8; delay(3); ISR_SW8(); break;

	//default: PRINT(PCINT ERROR)
  }
  endstop_state=ENDSTOPS;
  PCMSK2 = 0xFF;
}


void ISR_SW1(){ //Endstop M1_HIGH

	disableMotor(M1);
	setDir(M1,DOWN);
}

void ISR_SW2(){//Endstop M1_LOW

	disableMotor(M1);
	setDir(M1,UP);
	setPos(M1,0);
 #ifdef _BLOCK_
	unblock();
 #endif
}

void ISR_SW3(){//Endstop M2_HIGH

	disableMotor(M2);
	setDir(M2,DOWN);
}

void ISR_SW4(){//Endstop M2_LOW

	disableMotor(M2);
	setDir(M2,UP);
 	setPos(M2,0);
 #ifdef _BLOCK_
    unblock();
 #endif
}

void ISR_SW5(){//Endstop M3_RIGHT

	disableMotor(M3);
	setDir(M3,LEFT);
	setPos(M3,0);
  #ifdef _BLOCK_
	unblock();
  #endif
}

void ISR_SW6(){//Endstop M3_LEFT

	disableMotor(M3);
	setDir(M3,RIGHT);
}


void ISR_SW7(){//Position detector M3

  if(motor[M3].dir==LEFT){
 	if((ENDSTOPS & 1<<SW7)==0){ //Activo por nivel bajo

		motor[M3].pos++;
		if (getPos(M3)==getWantedPos(M3)){

			setDir(M3,RIGHT);
			//delay?
			disableMotor(M3);
	#ifdef _BLOCK_
			unblock();
	#endif
		}
	}
  }
  else if(motor[M3].dir==RIGHT){

	if((ENDSTOPS & 1<<SW7)){ //Inactivo por nivel alto

		motor[M3].pos--;
        }
  }
}



void ISR_SW8(){ //M4 step counter

	motor[M4].pos++;
	if (motor[M4].pos==YTURNCOUNT){

		motor[M4].pos=0;
  #ifdef _SYS_CALL_
		syscall_product_out();    //when M4 has been spinning for a while
  #endif
  }
}


ISR(SO3){//Optical Encoder M1

  EIMSK&= ~(1<<INT0);
  EIFR|=1<<INT0;
  if(motor[M1].dir==UP){

    motor[M1].pos++;
  }
  else{

    motor[M1].pos--;
  }

#ifdef _LIB_CALL_
  libcall_motorsync();
  libcall_motorZroutine();
#endif

  delay(50);
  EIMSK|= 1<<INT0;
}


ISR(SO4){//Optical Encoder M2

  EIMSK&= ~(1<<INT1);
  EIFR|=1<<INT1;
  if(motor[M2].dir==UP){

    motor[M2].pos++;
  }
  else{

    motor[M2].pos--;
  }

#ifdef _LIB_CALL_
  libcall_motorsync();
  libcall_motorZroutine();
#endif

  delay(50);
  EIMSK|=1<<INT1;
}


//ISR(SW10) Not needed, level sensors
//ISR(SW11)
