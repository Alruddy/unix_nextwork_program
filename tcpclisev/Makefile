PROGS = tcpserv01 tcpcli01
CC = gcc
CFLAGS = -g -Wall -O2
LIBS = -lpthread -lunp

all:	${PROGS}

tcpserv01: tcpserv01.o str_echo01.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

tcpcli01: tcpcli01.o str_cli01.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}
