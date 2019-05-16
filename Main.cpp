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
	
	startGame(7, 5, human, 2.0);
	
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
		board = computerTurn(initial_state, adepth);
	}
	
	while (1)
	{
		//ruch gracza:
		erase();
		board->display();
		if (board->isTerminal() == true)
		{
			printw("Koniec ruchów...");
			break;
		}
		board = humanTurn(board, getch() - 48);
		if (board->getH() == -INF)
		{
			erase();
			board->display();
			printw("Wygrana gracza!");
			break;
		}
		
		//ruch komputera:
		if (board->isTerminal() == true)
		{
			erase();
			board->display();
			printw("Koniec ruchów...");
			break;
		}
		board = computerTurn(board, adepth);
		if (board->getH() == INF)
		{
			erase();
			board->display();
			printw("Wygrana komputera...");
			break;
		}
	}
	
	getch();
	delete initial_state; //usunie rekurencyjnie wszystkie stany potomne
}

GameState* humanTurn(GameState* aobj, int acolumn)
{
	GameState* next_turn = NULL;
	do
	{
		next_turn = aobj->dropChecker(acolumn);
	} while (next_turn == NULL);
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

