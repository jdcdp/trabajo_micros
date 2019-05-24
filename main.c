/*
 * GccApplication4.c
 *
 * Created: 24/05/2019 9:37:40
 * Author : junti
 */ 

#define _SYS_CALL_ //Macro para integraci�n
#define _BLOCK_ //Determina si las instrucciones de movimiento son simult�neas or consecutivas

#include <avr/io.h>
#include "pinout.h"
#include "macros.h"
#include "teclado.h"
#include "motion.h"
#include "coin.h"
#include "drivers/time.h"





#define HOLD() while(1)	//activar sleep mode en vez de while(1)

void init(){ // Aqui se llaman a las funciones de inicializaci�n

 setup_time();
 setup_coin();
 setup_motion();
 //setup_teclado(); // Falta la integraci�n de esta parte
}


int main(){
  init();  
  HOLD();
return 0;
}

