CC = clang
CFLAGS = -g -Wall -Wextra -Werror -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: banhammer

banhammer: banhammer.o speck.o ht.o bst.o node.o bf.o bv.o parser.o 
	$(CC) -o banhammer banhammer.o speck.o ht.o bst.o node.o bf.o bv.o parser.o $(LFLAGS)

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c
ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c
bst.o: bst.c
	$(CC) $(CFLAGS) -c bst.c
node.o: node.c
	$(CC) $(CFLAGS) -c node.c
bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c
bv.o:bv.c
	$(CC) $(CFLAGS) -c bv.c
parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

clean: 
	rm -f *.o banhammer 
format:
	clang-format -i -style=file *.c *.h
scan-build: clean
	scan-build make 
