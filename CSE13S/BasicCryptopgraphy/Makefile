CC = clang
CFLAGS = -g -Wall -Wextra -Werror -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: encrypt decrypt keygen

encrypt: encrypt.o randstate.o numtheory.o rsa.o
	$(CC) -o encrypt encrypt.o randstate.o numtheory.o rsa.o $(LFLAGS)
decrypt: decrypt.o randstate.o numtheory.o rsa.o
	$(CC) -o decrypt decrypt.o randstate.o numtheory.o rsa.o $(LFLAGS)
keygen: keygen.o randstate.o numtheory.o rsa.o 
	$(CC) -o keygen keygen.o randstate.o numtheory.o rsa.o $(LFLAGS)

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c
numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c
rsa.o: rsa.c
	$(CC) $(CFLAGS) -c rsa.c


clean: 
	rm -f *.o encrypt decrypt keygen
format:
	clang-format -i -style=file *.c *.h
scan-build: clean
	scan-build make 
