# File:   Makefile
# Author: Bailey Lissington, Dillon Pike
# Date:   12 Oct 2020
# Descr:  Makefile for paper scissors rock game.

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files. Add to game.o line.
game.o: game.c ../../drivers/avr/system.h ../../drivers/avr/ir_uart.h ../../drivers/display.h ../../drivers/navswitch.h ../../fonts/font5x7_1.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/button.h intro.h choice.h icons.h transmission.h result.h message.h game_constants.h hardware.h
	$(CC) -c $(CFLAGS) $< -o $@

intro.o: intro.c ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/navswitch.h message.h hardware.h
	$(CC) -c $(CFLAGS) $< -o $@

choice.o: choice.c ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/navswitch.h ../../drivers/button.h icons.h message.h hardware.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

icons.o: icons.c ../../drivers/ledmat.c
	$(CC) -c $(CFLAGS) $< -o $@

transmission.o: transmission.c ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/avr/ir_uart.h game_constants.h
	$(CC) -c $(CFLAGS) $< -o $@

result.o: result.c ../../utils/tinygl.h message.h game_constants.h
	$(CC) -c $(CFLAGS) $< -o $@

message.o: message.c ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

hardware.o: hardware.c ../../drivers/navswitch.h ../../drivers/button.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
game.out: game.o ir_uart.o usart1.o system.o pio.o prescale.o timer.o timer0.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o intro.o choice.o icons.o transmission.o result.o button.o message.o hardware.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


