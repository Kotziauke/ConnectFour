#include "GameState.h"
#include "AlphaBeta.h"

void ncurses_init();
void ncurses_quit();

int main(int argc, char* argv[])
{
	ncurses_init();
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
		erase();
		board->display();
		if (board->getChildren().empty() == true)
		{
			printw("Koniec ruchów...");
			break;
		}
		GameState* next_turn = NULL;
		do
		{
			int column = getch() - 48;
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
			printw("Wygrana gracza!");
			break;
		}
		
		//ruch komputera:
		board->display();
		if (board->getChildren().empty() == true)
		{
			printw("Koniec ruchów...");
			break;
		}
		std::pair<double, State*> p = alphaBeta(board, depth, -INFINITY, INFINITY);
		board = dynamic_cast<GameState*>(p.second->getRootMove());
		board->makeRoot();
		if (board->getH() == INF)
		{
			board->display();
			printw("Wygrana komputera...");
			break;
		}
	}
	getch();
	delete initial_state; //usunie rekurencyjnie wszystkie stany potomne
	
	
	ncurses_quit();
	return 0;
}

void ncurses_init()
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


void ncurses_quit()
{
	endwin();
}

