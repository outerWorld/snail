CC=g++
SLIB=
TESTS=test_ictclas test_word_dic
LFLAGS=-DOS_LINUX -g
CFLGAS=-DOS_LINUX -g -Werror
INC=-I./ -I../include
# for determining the status of os
MACH=$(`uname -m`)
HDW=$(`uname -i`)
CPU=$(`uname -p`)
VER=$(if ${MACH}=="i686"||${HDW}=="i386",32,64)
LIB=-L../lib -lICTCLAS50_${VER}

SLIB+=../lib/libICTCLAS50_${VER}.a 
SLIB+=../lib/libsnail.a

test_ictclas:test_ictclas.o ${SLIB}
	${CC} -o $@ $^ ${LFLAGS}

test_word_dic:test_word_dic.o ${SLIB}
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
