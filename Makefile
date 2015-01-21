# author : Julian Martinez del Campo
# class  : CMPT 464
# date   : October 17, 2014
#
# Makefile for morse code printer
SHELL=/bin/bash
CC=msp430-gcc
CFLAGS=-mmcu=msp430f1611 -DEMBEDDED -Wall -g -pedantic -std=c99
LDFLAGS=-mmcu=msp430f1611

.PHONY: clean

all: mctx

leds.o: leds.h

uart.o: uart.h

error.o: error.c

character.o: character.h

attributes.o: attributes.c

queue.o: queue_circular_array.c
	$(CC) $(CFLAGS) -c $< -o queue.o

timer.o: timer.h

morse_code.o: morse_code.h

main.o: main.c

mctx: leds.o main.o uart.o error.o attributes.o queue.o character.o timer.o morse_code.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	$(RM) *.o mctx
