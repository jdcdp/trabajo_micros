#ifndef _BARRERA_H_
#define _BARRERA_H_


#include <stdint.h>
#define SW9PIN	(PINB & 0x02)
#define SW9PORT	(PORTB & 0x02)

void abrir_puerta();

void cerrar_puerta();

#endif
