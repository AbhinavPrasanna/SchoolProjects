CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: tsp graph.o path.o stack.o

tsp: tsp.o graph.o path.o stack.o	
	$(CC) -o tsp tsp.o graph.o path.o stack.o $(LFLAGS)

tsp.o:tsp.c graph.h path.h stack.h vertices.h 
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	        $(CC) $(CLAGS) -c graph.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

stack.o:stack.c
		$(CC) $(CFLAGS) -c stack.c
clean:
	        rm -f tsp tsp.o graph.o path.o stack.o 
format:
	clang-format -i -style=file *.[ch]
