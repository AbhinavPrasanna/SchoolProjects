CC=clang
CFLAGS=-Wall -Wextra -Werror -Wpedantic

all:encode decode 

encode: encode.o io.o code.o huffman.o pq.o node.o stack.o 
	$(CC) -o $@ $^

decode: decode.o io.o code.o huffman.o pq.o stack.o node.o 
	$(CC) -o $@ $^

%.o: %.c
	clang $(CFLAGS) -c $<

clean: 
	rm -f *.o encode decode

format:
	clang-format -i -style=file *.[ch]

scan-build:clean
	scan-build make
