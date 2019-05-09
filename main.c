#include <avr/io.h>
#include "pinout.h"
#include "macros.h"
#include "teclado.h"
#include "motion.h"
#include "coin.h"
#define _SYS_CALL_
#define HOLD() while(1)	//activar sleep mode en vez de while(1)

uint8_t choque = 0;

void init(){
// Aqui se llaman a las funciones de inicialización
  motion_init();
  time_init();
  setup_coin();
  setup_teclado();        //setup del teclado en ultimo para no poder influir durante el setup de los otros
}

void change_choque(){
  if (choque == 0)
    choque = 1;
  else choque = 0;
}

void dispensado(){                     //Hay que llamar esta funciòn cuando llegamos al punto de sacar un producto
    if (saldo>=1.20 && getState == 1){ //comprueba que el saldo esta suficiente y verifica que estamos en la posicion de sacar producto
      while (choque == 0 || MAX_GIROS == 0){          
        moveY();                        //girar M4
        if (MAX_GIROS == 1){
          stopY();                      //hasta que llega al maximo de giros 
          change_led();                 //encender el LED si el producto esta agotado
          homeALL();
          change_led();                 //apaga el LED una vez llegamos al home
          already_selected = 0;         //ya no estamos en el proceso de sacar un producto
        }
        else if (choque == 1){          //o hasta que hay un producto que cae
          saldo -= 1.20;                //una vez llegado el producto, sustraer el dinero correspondiente
          stopY();
          homeALL();                    //volver a poner a home los motores
          already_selected = 0;         //ya no estamos en el proceso de sacar un producto
        }
      }
      change_choque = 0;                //volver a poner el estado de la variable choque a 0
    }
}

int main(){
  init();
  HOLD();
  return 0;
}

