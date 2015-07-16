#Makefile for the wd program.

PREFIX = /usr
TARGET = wd

CC = gcc
CFLAGS = -Wall -W -Wextra -O3 -fexpensive-optimizations\
-funroll-loops -fno-builtin -s -ansi -pedantic -std=c99
LIBS = -lm

all: ${TARGET}
	@echo made ${TARGET}
${TARGET}: ${TARGET}.c
	${CC} ${CFLAGS} ${TARGET}.c ${LIBS} -o ${TARGET}

clean:
	rm -rf ${TARGET}

install: all
	cp ${TARGET} ${PREFIX}/bin
	cp ${TARGET}.1 ${PREFIX}/share/man/man1

uninstall:
	rm -f ${PREFIX}/bin/${TARGET}
	rm -f ${PREFIX}/share/man/man1/${TARGET}.1
