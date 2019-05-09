#ifndef _TECLADO_H_
#define _TECLADO_H_

//Funciones integración

void nothing_selected();
void setup_teclado();

//Funciones 

void debounceMs(); //Antirrebotes_beta
void delayMs(); //Función de retardo en ms bloqueante
void position(); //Envía la posición seleccionada 
void blink_led(); //Hace parpadear el led si ya hay un producto seleccionado


#endif
