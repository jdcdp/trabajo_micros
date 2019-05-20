/*
 * prueba.c
 *
 * Created: 20/05/2019 11:23:09
 * Author : junti
 */ 

#include <avr/io.h>
#include "pinout.h"
#include "macros.h"
#include "teclado.h"
#include "motion.h"
#include "coin.h"
#include "drivers/time.h"
#define _SYS_CALL_

#define HOLD() while(1)	//activar sleep mode en vez de while(1)

void init(){
// Aqui se llaman a las funciones de inicialización
 motion_init();
 time_init();
}


int main(){
  init();
  //setDir(M1,UP);
  //setDir(M2,UP);
  // homeZ();
  //homeX();

  HOLD();
return 0;
}



