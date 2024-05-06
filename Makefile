SRC = $(wildcard *.c)
POST_OUT = -o Dictionary.out
GCCST = gcc -flto
TEST = tests/test
HASHMAP_T = hashmap_t.c

build :
	GCCST ${SRC} ${POST_OUT}
	
buildTest :
	GCCST ${TEST}.c ${HASHMAP_T} -o ${TEST}.out
	
Test :
	./runTest.sh
