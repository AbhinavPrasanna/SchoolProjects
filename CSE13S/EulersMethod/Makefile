CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all:  mathlib-test newton.o euler.o e.o madhava.o bbp.o viete.o

mathlib-test: mathlib-test.o newton.o euler.o e.o madhava.o bbp.o viete.o
	  $(CC) -o mathlib-test mathlib-test.o newton.o euler.o e.o madhava.o bbp.o viete.o $(LFLAGS)

mathlib-test.o:mathlib-test.c
	 $(CC) $(CFLAGS) -c mathlib-test.c

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -c newton.c

euler.o: euler.c mathlib.h
	 $(CC) $(CFLAGS) -c euler.c

e.o:e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

madhava.o: madhava.c mathlib.h
	$(CC) $(CFLAGS) -c madhava.c

bbp.o: bbp.c mathlib.h
	 $(CC) $(CFLAGS) -c bbp.c

viete.o: viete.c mathlib.h
	$(CC) $(CFLAGS) -c viete.c
clean:
	rm -f mathlib-test mathlib-test.o newton.o euler.o e.o madhava.o bbp.o viete.o

format:
	clang-format -i -style=file *.[ch]
