/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


#include "pinout.h"

ISR(PCINT0_vect){
 //Mascara para tu pin SW9
 //Frenar Motor
 M5_EN=0;
 M5_BK=1;

}
void abrir_puerta(){
//comprobar el estado de SW9, si esta en la posicion de cerrado, accionar m5
  if(isSet( P, B )){
     M5_EN=1;
        
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

*/