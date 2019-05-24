
# Documentación de las librerias


## Funciones comunes:

&nbsp;

-   *max(a,b)*: devuelve el máximo

-   *min(a,b)*: devuelve el mínimo

-   *changePin(port,pin,val)*: cambia un pin de un puerto
-   *abs(a):* devuelve el valor absoluto


&nbsp;

&nbsp;

## teclado (teclado.h):

**Funciones:**

- *setup_teclado():* Inicializa el teclado

- *product_out():* función que se llama cuando no hay producto para encender LED y seleccionar de nuevo

- *choose_again():* función para dejar seleccionar si el consumidor cambia de idea.

## Sensor de monedas(coin.h):

**Funciones:**

-   *setup_coin():* Inicialización de la libreria

-   *get_saldo():* calcula el saldo

-   *get_ultima_moneda():* coge el valor de la última moneda introducida

-   *not_aligned():* Avisa de que no se debe mover al dispensador todavia

-   *substract_saldo(uint8_t gasto):* resta el saldo correspondiente(activar con piezoelectrico)

-   *syscall_aligned():* notifica al sistema de que los motores están en posición.


&nbsp;

**Interrupciones:**

-   *Sensores Ópticos 1 y 2 (SO1,SO2):*

**Llamadas externas:**

-   *moveY():* Para el dispensado y vuelve al la posición de descanso



## Control del movimiento(motion.h):

**Funciones:**

  - *void homeAll()*: hace un home para todos los ejes

  - *void homeZ()*: home vertical hacia abajo

  - *void homeX()*: home horizontal hacia la derecha

  - *void moveZ(uint16_t position)*: posicion manual del eje z, no es necesaria

  - *void moveX(uint8_t position)*: posicion manual del eje x, no es necesaria

  - *void moveY()*: activa el dispensador

  - *void stopY()*: para el dispensador y vuelve a posición de reposo

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

-   *syscall_aligned():* notifica al sistema de que los motores están en posición para el dispensado


## Esquema de pines

![image0001](ejemplos/image0001.png)


## Explicación y flujogramas


- **Parte 1: Motores y e integración del movimiento**

El código de los motores tiene una ligera inspiración de la programación orientada a objetos: todas las variables se encuentran contenidas en structs (motor1, motor2 etc) y se implementan métodos para cambiar o consultar estos valores.

 La librería motion.c está formada por funciones de alto nivel con una sintaxis muy básica: funciones del tipo moveX(), moveY(), homeZ. Su función es evidente y su implementación muy sencilla.

El resto de librerias se encuentran en la carpeta /drivers/ y en su mayoría son funciones de bajo nivel: disableMotor(), setSpeed(), setDir(), pwm(). Esto incluye a las rutinas de interrupción (en motor.c).

La filosofía de esta parte del programa es dejar que el control del sistema lo realizen enteramente las interrupciones: por ejemplo moveX() solo pone en movimiento al motor en la dirección adecuada, mientras que la parada en el lugar adecuado deberá realizarla la rutina de interrupción de SW7. Esto hace el sistema bastante robusto debido a que las funciones son sencillas y poco vulnerables a errores. Sin embargo plantea un problema en la temporalidad de la ejecución, ya que si ejecuto moveX();moveX(); se van a mover simultáneamente. La solución es detener la ejecución de cada comando hasta que haya algun cambio en uno de los endstops, y de esto se encargan las funciones block y unblock(Que a pesar de su nombre no son bloqueantes, permiten todas las interrupciones)


Flujograma ejemplo M3:

<div class="mxgraph" style="max-width:100%;border:1px solid transparent;" data-mxgraph="{&quot;highlight&quot;:&quot;#0000ff&quot;,&quot;nav&quot;:true,&quot;resize&quot;:true,&quot;toolbar&quot;:&quot;zoom layers lightbox&quot;,&quot;edit&quot;:&quot;_blank&quot;,&quot;xml&quot;:&quot;&lt;mxfile modified=\&quot;2019-05-24T10:03:14.479Z\&quot; host=\&quot;www.draw.io\&quot; agent=\&quot;Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36\&quot; etag=\&quot;JhVQ2S2CBeVXiTj8Aj0_\&quot; version=\&quot;10.6.8\&quot; type=\&quot;device\&quot;&gt;&lt;diagram id=\&quot;PwTy0VUJICKudSSfvR86\&quot; name=\&quot;Page-1\&quot;&gt;7Vpdj5s4FP01kdKHjsBgQh4zmXS33Uk1albq9GllwAm0gFnjfPXXrwETjCEJM0OaHU2lkYZ7fDG27z3H15CBMY12f1CU+HPi4XAANG83MO4GAOjG2OT/MmRfIKOxVQArGnjCqQIWwU8sQE2g68DDac2RERKyIKmDLolj7LIahigl27rbkoT1pyZohRvAwkVhE/0aeMwvUBuMKvxPHKz88sm6NS5aIlQ6i5mkPvLIVoKM2cCYUkJYcRXtpjjMFq9cl+K+D0daDwOjOGZdbjDMSHf+uf/+178zd/3pk/N+Q9z3Yhop25cTxh6fvzAJZT5ZkRiFswq9pWQdezjrVeNW5XNPSMJBnYPfMWN7EUy0ZoRDPotC0Yp3AXvMbr+BwvomtdztRM+5sZeMB0yDCDNMBVaMPRvw0SURUErW1MUn1qFMLURXmJ3wMw+B4xmPCR8N3fP7KA4RCzb1cSCRequDn7h1QinaSw4JCWKWSj0/ZAB3ECwCY5FCgkMAKpF+mj+/KEZQWtJUKijPnidkkpj0BoVrsQwDYIV8LW/TBMX8esXykBWYUwJzssGPQ+Nd2cCf7ajOHGvtg1aIksQpo+THgbCgnn6ciEnmF+1WmWbdLEOydX1E2Q1PrSiIESM8w263fsDwIkF53my5J8eWQRhOSZi188cYHsS2Z2Zd5s+TWmzgGJZ1GNoGU4Z3p7O0mVVlOM16OHULFva2EiRdEz6+JEaWdjwRpWR4Rqz1xor/T2WjR4kwO0qErrVHs7NGvCg0ZoOGKWZ3AR3ezz78/a6NOidIevDifSwSjL3hfPJ4opMmolAXx8gJ8Zxwhg3nFenPsfuIDCgpWCWYfoS+UjIhJyXhmuEJdUXC5WhlVbSWZUQVAITtpdsmAJZrY2fZkwBosK7npb7LAjBqEQDdvJQCgPFVFCDmY5ckIDO/lbTPjEoEcmsvW5esHrSO2gDsa2pDOcwze3SyjTg5B2Aqk/03+QT5TPvq5NPN17L9tlXtzyVxn3wFXfl6JDeeVu83CnRLySmjtMsuioGJu5Rs6aNWB88r1j8uvgwXX0e/i/XjcgFhPbTXL9aB1Qj2Z3JNAdEl+ajE5DrHfthVCGAfQvDUg/8I1E9+8MzBX/W31VdCZ3RI8b/QiwLYrQohfGG0rD1z0bYoZth7yMBuBckzVcXDbpAGJO6mKUvbxW5rCeLY0IRaT5qi18PaWoKMf239/2peHPapFtavUouXlYdNwW8jmBekrYfxN1vpQwBu6npoWS1EKzf0GtEAvFAwQfPMthhMjcHkrknA2JtkXzy45YYoTQP3MgX8NfbfIqeboZMCA1sEsMReWK/DkbIP20q4i4k26vXmhqsouaUpAn3hwh8Yb1C2D98NzybZVWW77Fhiel7u3OZ/b0aElfOTobdIcNv5SVep1F9gmgXrF8zWNO6r5nwdJ1kbdozE5U6y9psMhPr9z7pgILhZ/SKh2HWq33UYs/8A&lt;/diagram&gt;&lt;/mxfile&gt;&quot;}"></div>
<script type="text/javascript" src="https://www.draw.io/js/viewer.min.js"></script>

Como ultimo comentario sobre esta parte del código también existe soporte para mover la máquina expendedora a una posición dada, incluyendo así parte de la integración. La funcion selectProduct() mueve la expendedora a la posicicion adecuada para el dispensado y avisa al sistema mediante la función syscall_alligned() (que deberá implementarse en la integración ). La función stopY() detiene el dispensado y pone a los motores en la posición de origen.
