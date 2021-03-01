CC = g++
FLAGS = -Wextra -Wall -Wvla -std=c++17 -g
OBJECTS = Ex2.o ChessGame.o ChessBoard.o ChessPiece.o Pawn.o Rook.o Knight.o Queen.o \
King.o Bishop.o
FILES = Ex2.cpp ChessGame.cpp ChessBoard.cpp ChessPiece.cpp Pawn.cpp Rook.cpp Knight.cpp Queen.cpp \
King.cpp Bishop.cpp ChessGame.h ChessBoard.h ChessPiece.h Pawn.h Rook.h Knight.h Queen.h \
King.h Bishop.h Makefile README


all : chess
	
chess : $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o chess

Ex2.o : Ex2.cpp ChessGame.h ChessGame.cpp
	$(CC) $(FLAGS) -c Ex2.cpp

ChessGame.o : ChessGame.h ChessGame.cpp ChessBoard.h ChessBoard.cpp
	$(CC) $(FLAGS) -c ChessGame.cpp

ChessBoard.o : ChessBoard.h ChessBoard.cpp Pawn.h Pawn.cpp Rook.h Rook.cpp Knight.h Knight.cpp \
Bishop.h Bishop.cpp Queen.h Queen.cpp King.h King.cpp
	$(CC) $(FLAGS) -c ChessBoard.cpp

ChessPiece.o : ChessPiece.h ChessPiece.cpp ChessBoard.h ChessBoard.cpp
	$(CC) $(FLAGS) -c ChessPiece.cpp

Pawn.o : Pawn.h Pawn.cpp ChessPiece.h ChessPiece.cpp
	$(CC) $(FLAGS) -c Pawn.cpp

Rook.o : Rook.h Rook.cpp ChessPiece.h ChessPiece.cpp
	$(CC) $(FLAGS) -c Rook.cpp

Knight.o : Knight.h Knight.cpp ChessPiece.h ChessPiece.cpp
	$(CC) $(FLAGS) -c Knight.cpp

Bishop.o : Bishop.h Bishop.cpp ChessPiece.h ChessPiece.cpp
	$(CC) $(FLAGS) -c Bishop.cpp

Queen.o : Queen.h Queen.cpp ChessPiece.h ChessPiece.cpp
	$(CC) $(FLAGS) -c Queen.cpp

King.o : King.h King.cpp ChessPiece.h ChessPiece.cpp
	$(CC) $(FLAGS) -c King.cpp

tar :
	tar -cvf ex2.tar $(FILES)
clean :
	-rm -f *.o $(OBJECTS)

.PHONY: clean

