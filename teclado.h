#ifndef _TECLADO_H_
#define _TECLADO_H_

//Funciones integración

void syscall_product_out();
void setup_teclado();
void choose_again();

//Funciones 

void debounceMs(); //Antirrebotes_beta
void position(); //Envía la posición seleccionada 
void blink_led(); //Hace parpadear el led si ya hay un producto seleccionado


#endif