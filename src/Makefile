CC=g++
CFLAG=-g
LFLAG=
INC=-I../include
ALL_OBJS=
include Makefile.am
ALL_OBJS+=${OBJS}

%.o:%.cpp
	${CC} ${CFLAG} -c $< ${INC}

.PHONY:all clean_objs clean_all

all:${ALL_OBJS}

clean_objs:
	rm -f *.o

clean_all:clean_objs
