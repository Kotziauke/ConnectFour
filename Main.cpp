#include <cstdlib>
#include <ctime>
#include "GameState.h"
#include "AlphaBeta.h"

void ncursesInit();
void ncursesQuit();
void startGame(int awidth, int aheight, Player awho_starts, double adepth);
GameState* humanTurn(GameState* aobj, int acolumn);
GameState* computerTurn(GameState* aobj, double adepth);

int main(int argc, char* argv[])
{
	ncursesInit();
	
	startGame(7, 5, computer, 2.0);
	
	ncursesQuit();
	return 0;
}

void ncursesInit()
{
	initscr();
	raw();
	keypad(stdscr, true);
	noecho();
	start_color();
	use_default_colors();
	curs_set(0);
	init_pair(pair_human, COLOR_BLUE, -1);
	init_pair(pair_computer, COLOR_RED, -1);
	init_pair(pair_empty, COLOR_BLACK, -1);
	init_pair(pair_cursor, COLOR_YELLOW, -1);
}

void ncursesQuit()
{
	endwin();
}

void startGame(int awidth, int aheight, Player awho_starts, double adepth)
{
	GameState* initial_state = new GameState{ awho_starts, awidth, aheight };
	GameState* board = NULL;
	if (awho_starts == human)
	{
		board = initial_state;
	}
	else
	{
		srand(time(NULL));
		board = humanTurn(initial_state, rand() % awidth);
	}
	int column = awidth / 2;
	
	while (1)
	{
		//ruch gracza:
		if (board->isTerminal() == true)
		{
			board->displayWithCursor(column);
			printw("Koniec ruchów...");
			break;
		}
		while (1)
		{
			board->displayWithCursor(column);
			GameState* turn = NULL;
			switch (getch())
			{
			case 260: //left
				if (column > 0)
				{
					column--;
				}
				break;
			case 261: //right
				if (column < awidth - 1)
				{
					column++;
				}
				break;
			case 32: //space
				turn = humanTurn(board, column);
				break;
			case 27: //escape
				delete initial_state;
				return;
			}
			if (turn != NULL)
			{
				board = turn;
				break;
			}
		}
		//board = humanTurn(board, getch() - 48);
		if (board->getH() == -INF)
		{
			board->displayWithCursor(column);
			printw("Wygrana gracza!");
			break;
		}
		
		//ruch komputera:
		if (board->isTerminal() == true)
		{
			board->displayWithCursor(column);
			printw("Koniec ruchów...");
			break;
		}
		board = computerTurn(board, adepth);
		if (board->getH() == INF)
		{
			board->displayWithCursor(column);
			printw("Wygrana komputera...");
			break;
		}
	}
	
	getch();
	delete initial_state; //usunie rekurencyjnie wszystkie stany potomne
}

GameState* humanTurn(GameState* aobj, int acolumn)
{
	GameState* next_turn = aobj->dropChecker(acolumn);
	if (next_turn == NULL)
	{
		return NULL;
	}
	aobj = next_turn;
	aobj->makeRoot();
	return aobj;
}

GameState* computerTurn(GameState* aobj, double adepth)
{
	std::pair<double, State*> turn = alphaBeta(aobj, adepth, -INFINITY, INFINITY);
	aobj = dynamic_cast<GameState*>(turn.second->getRootMove());
	aobj->makeRoot();
	return aobj;
}

