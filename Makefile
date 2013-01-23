CC=g++

.PHONY:clean all

tests:
	cd test && make clean && make || cd ..

all:libs tests

clean_tests:
	cd test && make clean || cd ..

clean_libs:
	@echo "to clean object"

clean_all:clean_libs clean_tests
