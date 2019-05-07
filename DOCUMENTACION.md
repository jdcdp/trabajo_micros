
# Documentación de las librerias


## Funciones comunes:

&nbsp;

-   *max(a,b)*: devuelve el máximo

-   *min(a,b)*: devuelve el mínimo

&nbsp;

&nbsp;

## Sensor de monedas(coin.h):

**Funciones:**

-   *setup_coin :* Inicialización de la libreria

-   *get_saldo:* calcula el saldo

-   *get_ultima_moneda :* coge el valor de la última moneda introducida


&nbsp;

**Interrupciones:**

-   *Sensores Ópticos 1 y 2 (SO1,SO2):*

**Llamadas externas:**

-   *syscall_leer_saldo();*: Avisa al sistema del estado del saldo


## Control del movimiento(motion.h):

**Funciones:**

  - *void homeAll()*: hace un home para todos los ejes

  - *void homeZ()*: home vertical hacia abajo

  - *void homeX()*: home horizontal hacia la derecha

  - *void moveZ(uint16_t position)*: posicion manual del eje z, no es necesaria

  - *void moveX(uint8_t position)*: posicion manual del eje x, no es necesaria

  - *void moveY()*: activa el dispensador

  - *void stopY()*: para el dispensador

  - *uint8_t getState()*: de momento no hace nada pero puede servir para dar  información de la posicion actual

   - *void releaseProduct(uint8_t num)*: Se posiciona en el producto "num" segun la siguiente tabla:

&nbsp;

| 1 | 2 | 3 |
|---|---|---|
| 4 | 5 | 6 |
| 7 | 8 | 9 |

&nbsp;
**Interrupciones:**

- SW1 to SW6 : Endstops M1_HIGH/LOW hasta M3_HIGH/LOW (Puerto K)

- SO3 : Optical Encoder del motor M1 (vertical) (INT0)

- SO4 : Optical Encoder del motor M2 (vertical) (INT1)

- SW7 : Detector de posicion M3 (puerto K)

&nbsp;
**Llamadas externas:**

-   *syscall_product_out():* notifica al sistema que se ha agotado el producto que se ha pedido

-   *syscall_aligned():* notifica al sistema de que los motores están en posición.
