#include <avr/io.h>
#include "teclado.h"
#include "motion.h"
#include "coin.h"
#define HOLD() while(1)	//activar sleep mode en vez de while(1)

void init(){
// Aqui se llaman a las funciones de inicialización
motion_init();

}


int main(){
  init();
  HOLD();
return 0;
}

