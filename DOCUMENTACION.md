
# Documentación de las librerias

##Control del movimiento(motion.h):

**void homeAll()**: hace un home para todos los ejes

**void homeZ()**: home vertical hacia abajo

**void homeX()**: home horizontal hacia la derecha

**void moveZ(uint16_t position)**: posicion manual del eje z, no es necesaria

**void moveX(uint8_t position)**: posicion manual del eje x, no es necesaria

**void moveY()**: activa el dispensador

**void stopY()**: para el dispensador

**uint8_t getState()**: de momento no hace nada pero puede servir para dar  información de la posicion actual

**void releaseProduct(uint8_t num)**: Se posiciona en el producto "num" segun la siguiente tabla:



| 1 | 2 | 3 |
|---|---|---|
| 4 | 5 | 6 |
| 7 | 8 | 9 |
