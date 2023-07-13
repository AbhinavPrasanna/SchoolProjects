#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                     makes Sparse
#  make ListClient         makes ListClient
#  make MatrixClient       makes MatrixClient
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o $(BASE_OBJECTS)
	$(LINK) Sparse Sparse.o $(BASE_OBJECTS)

ListClient : ListClient.o $(BASE_OBJECTS)
	$(LINK) ListClient ListClient.o $(BASE_OBJECTS)

Sparse.o : Sparse.c $(HEADERS)
	$(COMPILE) Sparse.c

ListClient.o : ListClient.c $(HEADERS)
	$(COMPILE) ListClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) Sparse ListClient Sparse.o ListClient.o $(BASE_OBJECTS)

checkFind : FindComponents
	$(MEMCHECK) FindComponents in8 junk8

checkClient : GraphClient
	$(MEMCHECK) GraphClient
