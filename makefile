# Máquina expendedora

all: *.c drivers/*.c
	avr-gcc *.c drivers/*.c -mmcu=atmega640 -o test

main: main.c
	avr-gcc main.c -mmcu=atmega640 -o test

motion: main.c motion.c
	avr-gcc main.c motion.c drivers/*.c -mmcu=atmega640 -o test
