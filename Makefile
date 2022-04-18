output: compile-all
	g++ main.o board.o engine.o moves.o -o main

compile-all: board.o engine.o moves.o main.o

board.o: board.h
	g++ -c board.cpp
engine.o: engine.h
	g++ -c engine.cpp
moves.o: moves.h
	g++ -c moves.cpp
main.o:
	g++ -c main.cpp

clean:
	@rm -f main.o board.o engine.o moves.o main
