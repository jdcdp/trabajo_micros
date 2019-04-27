# Máquina expendedora

all: *.c drivers/*.c
	avr-gcc *.c drivers/*.c -o test
