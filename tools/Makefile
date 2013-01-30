CC=g++
CFLAGS=-g
LDFLAGS=
INC=-I../include
LNK_SLIB=../lib/libsnail.a
LNK_DLIB=-I/usr/lib -liconv
TOOLS=gen_dic

gen_dic:gen_dic.o ${LNK_SLIB}
	${CC} -o $@ $^ ${LNK_DLIB}

%.o:%.cpp
	${CC} -c $< ${INC} ${CFLAGS}

.PHONY:clean all

all:${TOOLS}

clean_objs:
	rm -f *.o

clean:clean_objs
	rm -f ${TOOLS}
