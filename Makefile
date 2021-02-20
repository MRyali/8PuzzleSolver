
all: main.cpp puzzleSolver.o
	g++ main.cpp puzzleSolver.o

puzzleSolver: puzzleSolver.cpp puzzleSolver.h
	g++ -c puzzleSolver.cpp -o puzzleSolver.o
