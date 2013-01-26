CC=g++
AR=ar
LIBS=libsnail.a libsnail.so
LFLAGS=-g
LIB_OBJS=
include src/Makefile.am
LIB_OBJS+=$(foreach obj,${OBJS},src/${obj})

libsnail.a:${LIB_OBJS}
	${AR} rcs $@ $^
	mv $@ lib/

libsnail.so:${LIB_OBJS}
	${CC} -shared -o $@ $^
	mv $@ lib/

.PHONY:clean all tests

tests:
	cd test && make clean && make all && make clean_objs || cd ..

makeobjs:
	cd src && make clean_objs && make all || cd ..

libs:makeobjs ${LIBS} clean_objs

all:libs tests clean_objs

clean_tests:
	cd test && make clean || cd ..

clean_objs:
	cd src && make clean_objs || cd ..

clean_libs:
	cd lib && rm -f ${LIBS} || cd ..

clean_all:clean_libs clean_objs clean_tests
