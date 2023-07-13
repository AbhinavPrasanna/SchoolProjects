CC = clang
CFLAGS = -c -Wall -Wextra -Werror -pedantic

queue.o:    queue.c
	clang-format -i -style=file queue.c
	$(CC) $(CFLAGS) -o queue.o queue.c

clean:
	rm -f queue.o

all: queue.o 
