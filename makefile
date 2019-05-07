# Máquina expendedora

all: *.c drivers/*.c
	avr-gcc *.c drivers/*.c -mmcu=atmega640 -o test

main: main.c
	avr-gcc main.c -mmcu=atmega640 -o test

motion: main.c motion.c
	avr-gcc main.c motion.c -mmcu=atmega640 -o test

motor: main.c drivers/motor.c
	avr-gcc main.c drivers/motor.c -mmcu=atmega640 -o test

motionlibs: main.c motion.c drivers/motor.c drivers/pwm.c drivers/time.c
	avr-gcc main.c motion.c drivers/motor.c drivers/pwm.c drivers/time.c -mmcu=atmega640 -o test
