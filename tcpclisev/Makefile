PROGS = tcpserv01 tcpcli01\
        tcpserv02 tcpcli02\
        tcpserv03
CC = gcc
CFLAGS = -g -Wall -O2
LIBS = -lpthread -lunp

all:	${PROGS}

tcpserv01: tcpserv01.o str_echo01.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

tcpcli01: tcpcli01.o str_cli01.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

tcpserv02: tcpserv02.o str_echo01.o sigchilwait.o
	${CC} ${CFALGS} -o $@  tcpserv02.o str_echo01.o sigchilwait.o ${LIBS}

tcpcli02: tcpcli02.o str_cli01.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

tcpserv03: tcpserv03.o str_echo01.c sigchildwaitpid.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}
