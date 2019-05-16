Program : Main.o State.o GameState.o AlphaBeta.o Ncurses.o
	g++ Main.o State.o GameState.o AlphaBeta.o Ncurses.o -lncurses -o Program

Main.o : Main.cpp
	g++ -c Main.cpp

State.o: State.cpp State.h
	g++ -c State.cpp

GameState.o : GameState.cpp GameState.h
	g++ -c GameState.cpp

AlphaBeta.o : AlphaBeta.cpp AlphaBeta.h
	g++ -c AlphaBeta.cpp

Ncurses.o : Ncurses.cpp Ncurses.h
	g++ -c Ncurses.cpp

