//Archivo de integraciÃ³n

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
 setup_time();
 setup_coin();
 setup_motion();
 //setup_teclado();
}


int main(){
  init();  
  homeAll();
  moveZ(105); 
  moveX(2);
  moveZ(100);




  HOLD();
return 0;
}



