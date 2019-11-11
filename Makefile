#Abhi Mohnani
#amohnan1
#Makefile

CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra

# Links together files needed to create executable
chess: King.o Queen.o Rook.o Knight.o Bishop.o Pawn.o Board.o main.o Chess.o Mystery.o CreatePiece.o Terminal.o
	$(CC) -o King.o Queen.o Rook.o Knight.o Bishop.o Pawn.o Board.o main.o Chess.o Mystery.o CreatePiece.o Terminal.o

King.o: King.cpp King.h
	$(CC) $(CFLAGS) -c King.cpp

Queen.o: Queen.cpp Queen.h
	$(CC) $(CFLAGS) -c Queen.cpp

Rook.o: Rook.cpp Rook.h
	$(CC) $(CFLAGS) -c Rook.cpp

Knight.o: Knight.cpp Knight.h
	$(CC) $(CFLAGS) -c Knight.cpp

Bishop.o: Bishop.cpp Bishop.h
	$(CC) $(CFLAGS) -c Bishop.cpp

Pawn.o: Pawn.cpp Pawn.h
	$(CC) $(CFLAGS) -c Pawn.cpp

Board.o: Board.cpp Board.h
	$(CC) $(CFLAGS) -c Board.cpp

Chess.o: Chess.cpp Chess.h
	$(CC) $(CFLAGS) -c Chess.cpp

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

Mystery.o: Mystery.h
	$(CC) $(CFLAGS) -c Mystery.h

CreatePiece.o: CreatePiece.cpp CreatePiece.h
	$(CC) $(CFLAGS) -c CreatePiece.cpp

Terminal.o: Terminal.h
	$(CC) $(CFLAGS) -c Terminal.cpp

# Removes all object files,
# so we can start fresh
clean:
	rm -f *.o chess
