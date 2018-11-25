clean:
	rm -f $(wildcard *.o)
	rm -f $(wildcard *.so)

build: varint.c
	gcc -Wall -c -O3 -fPIC varint.c
	gcc -o libCMath.so -shared varint.o

rebuild: clean build
test: test.c clean build
	rm -f a.out
	gcc -Wall -o mathtest -L$(shell pwd) test.c -lCMath
	./mathtest
