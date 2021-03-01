CC = g++
FLAGS = -Wextra -Wall -Wvla -std=c++17
OBJECTS = Complex.o TimeChecker.o
FILES = Makefile Matrix.hpp TimeChecker.cpp README


	
all : $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o TimeChecker
	./TimeChecker 500
	
Matrix : Matrix.hpp.gch

TimeChecker.o : TimeChecker.cpp Matrix.hpp Complex.h Complex.cpp
	$(CC) $(FLAGS) -c TimeChecker.cpp
	
Complex.o : Complex.h Complex.cpp
	$(CC) $(FLAGS) -c Complex.cpp -o Complex.o


Matrix.hpp.gch : Matrix.hpp Complex.h Complex.o
	$(CC) $(FLAGS) -c Matrix.hpp


tar :
	tar -cvf ex3.tar $(FILES)
	
clean :
	-rm -f *.o Matrix.hpp.gch

.PHONY: clean
