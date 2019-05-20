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
 setup_motion();
 setup_coin();
 setup_teclado();
}


int main(){
  init();

  //moveZ(150);



  HOLD();
return 0;
}



