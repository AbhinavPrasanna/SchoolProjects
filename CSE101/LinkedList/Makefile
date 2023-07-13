#------------------------------------------------------------------------------
#  # Abhinav Prasanna, aprasann
# 2022 Spring CSE101 PA5
# Makefile for CSE 101 Programming Assignment 5
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
	g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++17 -Wall -c Shuffle.cpp

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

clean :
	rm -f Shuffle Shuffle.o ListClient ListClient.o List.o

check1 : ListTest
	valgrind --leak-check=full ListClient

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35
