CC=g++
TESTS=test_ictclas
LFLAGS=-DOS_LINUX -g
CFLGAS=-DOS_LINUX -g -Werror
INC=-I./ -I../include
LIB=-L../lib -lICTCLAS50_64
SLIB=../lib/libICTCLAS50_64.a
test_ictclas:test_ictclas.o ${SLIB}
	${CC} -o $@ $^ ${LFLAGS}

%.o:%.cpp
	${CC} -c $< ${CFLAGS} ${INC}

all:${TESTS}

.PHONY:clean all clean_objs

clean_objs:
	rm -f *.o

clean:
	rm -f ${TESTS}
	rm -f *.o
