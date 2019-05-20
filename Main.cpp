#include <cstdlib>
#include <ctime>
#include "GameState.h"
#include "AlphaBeta.h"
#include "Ncurses.h"

void startGame(int awidth, int aheight, Player awho_starts, double adepth);
GameState* humanTurn(GameState* aobj, int acolumn);
GameState* computerTurn(GameState* aobj, double adepth);

int main(int argc, char* argv[])
{
	ncursesInit();
	int option = 0;
	int width = 7;
	int height = 5;
	Player who_starts = human;
	double depth = 2.0;
	
	bool loop = true;
	while (loop)
	{
		erase();
		attrset(COLOR_PAIR(pair_yellow) | A_BOLD);
		printw("  # Connect 4 #\n");
		attrset(COLOR_PAIR(pair_yellow));
		printw("  Maciej Gabrys\n");
		printw("\n");
		attrset(COLOR_PAIR(pair_blue) | A_BOLD);
		printw("Rozmiar planszy:\n");
		attrset(COLOR_PAIR(pair_blue));
		printw("-szerokosc: ");
		printw(option == 0 ? "< %d >\n" : "  %d\n", width);
		printw("-wysokosc:  ");
		printw(option == 1 ? "< %d >\n" : "  %d\n", height);
		printw("\n");
		attrset(COLOR_PAIR(pair_red) | A_BOLD);
		printw("Poziom trudnosci:\n");
		attrset(COLOR_PAIR(pair_red));
		printw("-glebokosc: ");
		printw(option == 2 ? "< %.0lf >\n" : "  %.0lf\n", depth);
		printw("-zaczyna:  ");
		if (who_starts == human)
		{
			printw(option == 3 ? "< TY >\n" : "  TY\n");
		}
		else
		{
			printw(option == 3 ? "< SI >\n" : "  SI\n");
		}
		printw("\n");
		attrset(COLOR_PAIR(pair_green) | A_BOLD);
		printw(option == 4 ? "    [ START ]\n" : "      START\n");
		attrset(COLOR_PAIR(pair_green));
		printw(option == 5 ? "    [ WYJDZ ]\n" : "      WYJDZ\n");
		attrset(COLOR_PAIR(pair_default));
		switch (getch())
		{
		case 259: //up
			if (option > 0)
			{
				option--;
			}
			break;
		case 258: //down
			if(option < 5)
			{
				option++;
			}
			break;
		case 260: //left
			switch (option)
			{
			case 0: //width
				if (width > 4)
				{
					width--;
				}
				break;
			case 1: //height
				if (height > 4)
				{
					height--;
				}
				break;
			case 2: //depth
				if (depth > 1)
				{
					depth--;
				}
				break;
			case 3: //who_starts
				if (who_starts == human)
				{
					who_starts = computer;
				}
				else
				{
					who_starts = human;
				}
				break;
			}
			break;
		case 261: //right
			switch (option)
			{
			case 0: //width
				if (width < 9)
				{
					width++;
				}
				break;
			case 1: //height
				if (height < 9)
				{
					height++;
				}
				break;
			case 2: //depth
				if (depth < 3)
				{
					depth++;
				}
				break;
			case 3: //who_starts
				if (who_starts == human)
				{
					who_starts = computer;
				}
				else
				{
					who_starts = human;
				}
				break;
			}
			break;
		case 10: //return
			switch (option)
			{
			case 4: //start
				startGame(width, height, who_starts, depth);
				break;
			case 5: //exit
				loop = false;
				break;
			}
			break;
		case 27: //escape
			option = 5;
			break;
		}
	}
	ncursesQuit();
	return 0;
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
			board->displayWithCursor(column, "Koniec ruchow...");
			break;
		}
		while (1)
		{
			board->displayWithCursor(column, "Ruch gracza:");
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
			case 10: //return
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
		if (board->getH() == -INFINITY)
		{
			board->displayWithCursor(column, "Wygrana gracza!");
			break;
		}
		
		//ruch komputera:
		if (board->isTerminal() == true)
		{
			board->displayWithCursor(column, "Koniec ruchow...");
			break;
		}
		board->displayWithCursor(column, "Ruch komputera:");
		printw("Liczenie...\n");
		refresh();
		board = computerTurn(board, adepth);
		if (board->getH() == INFINITY)
		{
			board->displayWithCursor(column, "Wygrana komputera!");
			break;
		}
	}
	
	getch();
	
	printw("Zwalnianie pamieci...\n");
	refresh();
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

