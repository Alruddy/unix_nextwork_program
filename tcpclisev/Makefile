PROGS = tcpserv01 tcpcli01\
        tcpserv02 tcpcli02\
        tcpserv03\
        tcpcli04\
        tcpserv05 tcpcli05\
        tcpserv06
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

tcpcli04: tcpcli01.o str_cli02.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

tcpserv05: tcpserv05.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

tcpcli05: tcpcli01.o str_cli03.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

tcpserv06: tcpserv06.o
	${CC} ${CFALGS} -o $@ $^ ${LIBS}

clean:
	rm ${PROGS} *.o
