#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


#include "pinout.h"

void abrir_puerta(){
//comprobar el estado de SW9, si esta en la posicion de cerrado, accionar m5
  if(isSet( P, B )){
      Bk_ON();
        
      if(isClr( P, B )){
         Bk_OFF();
         }
    }
}



void cerrar_puerta(){
//comprobar el estado de SW9, si esta en la posición de abierto, accionar m5
  if(isClr( P, B )){
      Bk_ON();
         
      if(isSet( P, B )){
          Bk_OFF();
          }
        }
}

//Conviene manejar el motor m5 con la señal de frenado dinamico, para parar la barrera en su lugar exacto

