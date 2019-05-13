#include <iostream>
#include <cmath>
#include <utility>
#include "Constants.h"
#include "State.h"
#include "GameState.h"
#include "AlphaBeta.h"

int main(int argc, char* argv[])
{
	//ustawienia gry
	int board_width = 7;
	int board_height = 5;
	Player who_starts = human;
	double depth = 2.0;
	
	GameState* initial_state = new GameState{ who_starts, board_width, board_height };
	GameState* board = initial_state;
	while (1)
	{
		//ruch gracza:
		board->display();
		if (board->getChildren().empty() == true)
		{
			std::cout << "Koniec ruchów...";
			break;
		}
		GameState* next_turn = NULL;
		do
		{
			int column;
			std::cin >> column;
			if (column < 0 || column >= board_width)
			{
				continue;
			}
			next_turn = board->dropChecker(column);
		} while (next_turn == NULL);
		board = next_turn;
		board->makeRoot();
		if (board->getH() == -INF)
		{
			board->display();
			std::cout << "Wygrana gracza!" << std::endl;
			break;
		}
		
		//ruch komputera:
		board->display();
		if (board->getChildren().empty() == true)
		{
			std::cout << "Koniec ruchów...";
			break;
		}
		std::pair<double, State*> p = alphaBeta(board, depth, -INFINITY, INFINITY);
		board = dynamic_cast<GameState*>(p.second->getRootMove());
		board->makeRoot();
		if (board->getH() == INF)
		{
			board->display();
			std::cout << "Wygrana komputera..." << std::endl;
			break;
		}
	}
	delete initial_state; //usunie rekurencyjnie wszystkie stany potomne
	
	
	
	return 0;
}

