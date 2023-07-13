all: httpserver

httpserver: httpserver.o 
	clang -Wextra -Wpedantic -Wall -Werror -o httpserver httpserver.o asgn2_helper_funcs.a
	clang-format -i -style=file httpserver.c

httpserver.o: httpserver.c
	clang -Wextra -Wpedantic -Wall -Werror -c httpserver.c 

clean: 
	rm -f httpserver httpserver.o
