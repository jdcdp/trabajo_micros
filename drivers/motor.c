//AUTHOR: Jaime de Castro 14708

#include "motor.h"



void setSpeed(uint8_t motor,uint8_t spd){

speed[motor]=spd;

if(spd==0) {


}

}


ISR(SW1){   //aviso: estoy usando ints con todo, vamos a tener que usar PCints
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

ISR(SW6){
disableMotor(M3)
setDir(M3,LEFT)
}

ISR(SO3)
//codigo antirrebotes
if(motor[M1].dir==UP){
  motor[M1].pos++;
}
else{
  motor[M1].pos--;
}

ISR(SO4)
//codigo antirrebotes
if(motor[M2].dir==UP){
  motor[M2].pos++;
}
else{
  motor[M2].pos--;
}

