
/*
 * motores.h
 * Author : Telmo García-Verdugo 14172, Javier Colmenares 14082
 */

#ifndef MOTORES
#define MOTORES

 //////////////////////////////////////////////////////////////////////////

 #define ALTURA1 (35)							//altura de la fila 1
 #define ALTURA2 (100)							//altura de la fila 2
 #define POS_ENGRANE_1 (8)						//para bajar el motor 3 hasta posicion de engrane cuando vayamos a la fila 1
 #define POS_ENGRANE_2 (9)						//para bajar el motor 3 hasta posicion de engrane cuando vayamos a la fila 2
 #define POS_ENGRANE_3 (7)						//para bajar el motor 3 hasta posicion de engrane cuando vayamos a la fila 3
 #define POS_ENGRANE_0 (7)						//para subir el motor 3 cuando vayamos a la posicion inicial
 #define OVF_16MS (2)
 #define OVF_ON_PWM (7)							//tiempo encendido
 #define OVF_OFF_PWM (1)						//tiempo apagado

 //////////////////////////  FUNCIONES  ////////////////////////////////////

//funciones C
 void setup_variables();
 void setup_pines();
 void setup_motores();
 void reset_timer3();
 void reset_timer1();
 void pos_inicial();							//inicializa variables para mover a posicion inicial
 void mover (unsigned int);						//mueve el carro a la posición indicada (0 al 9)
 void M3_off_PWM();
 void M3_derecha_PWM();
 void M3_izquierda_PWM();

//funciones ensamblador	(funciones movimiento de los motores)
 void M1_off();									 
 void M2_off();
 void M3_off();
 void M1_arriba();
 void M1_abajo();
 void M2_arriba();
 void M2_abajo();
 void M3_derecha();
 void M3_izquierda();

#endif 