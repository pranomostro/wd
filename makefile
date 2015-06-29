#Makefile for the days program.

PREFIX = /usr
TARGET = days

CC = gcc
CFLAGS = -Wall -W -Wextra -O3 -fexpensive-optimizations -funroll-loops -fno-builtin -s -ansi -pedantic -std=c99
LIBS = -lm

all: ${TARGET} verf
	@echo made ${TARGET} and verf
${TARGET}: ${TARGET}.c
	${CC} ${CFLAGS} ${TARGET}.c ${LIBS} -o ${TARGET}
verf: verf.c
	${CC} ${CFLAGS} verf.c ${LIBS} -o verf

clean:
	rm -rf ${TARGET} verf

install: all
	cp ${TARGET} ${PREFIX}/bin
	cp ${TARGET}.1 ${PREFIX}/share/man/man1

uninstall:
	rm -f ${PREFIX}/bin/${TARGET}
	rm -f ${PREFIX}/share/man/man1/${TARGET}.1
