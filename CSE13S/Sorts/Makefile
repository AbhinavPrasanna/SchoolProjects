CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all:  sorting insert.o quick.o shell.o stats.o heap.o  

sorting: sorting.o insert.o quick.o shell.o stats.o heap.o 
	  $(CC) -o sorting sorting.o heap.o insert.o quick.o shell.o stats.o $(LFLAGS)

sorting.o:sorting.c insert.h quick.h set.h stats.h shell.h heap.h
	 $(CC) $(CFLAGS) -c sorting.c

heap.o: heap.c	
	$(CC) $(CLAGS) -c heap.c

insert.o: insert.c 
	 $(CC) $(CFLAGS) -c insert.c

quick.o:quick.c
	$(CC) $(CFLAGS) -c quick.c

shell.o: shell.c 
	$(CC) $(CFLAGS) -c shell.c 

stats.o: stats.c
	 $(CC) $(CFLAGS) -c stats.c

clean:
	rm -f sorting sorting.o heap.o insert.o quick.o shell.o stats.o 

format:
	clang-format -i -style=file *.[ch]
