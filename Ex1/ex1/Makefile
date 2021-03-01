CC = g++
FLAGS = -Wextra -Wall -Wvla -std=c++17 -pthread 

ex1 : Ex1.o Arenstorf.o ArenstorfPoint.o
	$(CC) $(FLAGS) Ex1.o Arenstorf.o ArenstorfPoint.o -o ex1

Ex1.o : Ex1.cpp Arenstorf.h Arenstorf.cpp ArenstorfPoint.h ArenstorfPoint.cpp
	$(CC) $(FLAGS) -c Ex1.cpp

Arenstorf.o : Arenstorf.h Arenstorf.cpp ArenstorfPoint.h ArenstorfPoint.cpp
	$(CC) $(FLAGS) -c Arenstorf.cpp

ArenstorfPoint.o : ArenstorfPoint.h ArenstorfPoint.cpp
	$(CC) $(FLAGS) -c ArenstorfPoint.cpp

clean :
	\rm *.o *~ ex1

