#Makefile for the day program.

CC = gcc
CFLAGS = -Wall -W -Wextra -O3 -fexpensive-optimizations -funroll-loops -fno-builtin -s -ansi -pedantic -std=c99
LIBS = -lm

all : days verf
	@echo made days and verf
days : days.c
	$(CC) $(CFLAGS) days.c $(LIBS) -o days
verf : verf.c
	$(CC) $(CFLAGS) verf.c $(LIBS) -o verf
