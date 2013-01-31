CC=g++
SLIB=
TESTS=test_ictclas test_word_dic test_lang_conv
LFLAGS=-DOS_LINUX -g
CFLGAS=-DOS_LINUX -g -Werror
INC=-I./ -I../include
# for determining the status of os
MACH=$(`uname -m`)
HDW=$(`uname -i`)
CPU=$(`uname -p`)
#VER=$(if ${MACH}==i686||${HDW}==i386,32,64)
VER=$(if "${MACH}"=="i686",32,64)
ifeq ("$(`uname -m`)", "i686")
VER=32
else
VER=64
endif
VER=32
LIB=-L../lib -lICTCLAS50_${VER}
SLIB+=../lib/libICTCLAS50_${VER}.a 
SLIB+=../lib/libsnail.a

test_ictclas:test_ictclas.o ${SLIB}
	echo "${VER} ${MACH}${HDW} ${CPU}"
	${CC} -o $@ $^ ${LFLAGS}

test_word_dic:test_word_dic.o ${SLIB}
	${CC} -o $@ $^ ${LFLAGS}
test_lang_conv:test_lang_conv.o ${SLIB}
	${CC} -o $@ $^ ${LFLAGS} -liconv

%.o:%.cpp
	${CC} -c $< ${CFLAGS} ${INC}

all:${TESTS}

.PHONY:clean all clean_objs

clean_objs:
	rm -f *.o

clean:
	rm -f ${TESTS}
	rm -f *.o
