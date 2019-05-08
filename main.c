#include <avr/io.h>
#include "pinout.h"
#include "macros.h"
#include "teclado.h"
#include "motion.h"
#include "coin.h"
#define _SYS_CALL_

#define HOLD() while(1)	//activar sleep mode en vez de while(1)

void init(){
// Aqui se llaman a las funciones de inicialización
motion_init();
time_init();
}


int main(){
  init();
  selectProduct(3);
  HOLD();
return 0;
}

