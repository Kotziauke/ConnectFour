Program : Main.o Constants.o State.o GameState.o AlphaBeta.o
	g++ Main.o Constants.o State.o GameState.o AlphaBeta.o -lncurses -o Program

Main.o : Main.cpp
	g++ -c Main.cpp

Constants.o : Constants.cpp Constants.h
	g++ -c Constants.cpp

State.o: State.cpp State.h
	g++ -c State.cpp

GameState.o : GameState.cpp GameState.h
	g++ -c GameState.cpp

AlphaBeta.o : AlphaBeta.cpp AlphaBeta.h
	g++ -c AlphaBeta.cpp

