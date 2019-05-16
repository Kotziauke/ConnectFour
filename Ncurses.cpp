#include "Ncurses.h"

void ncursesInit()
{
	initscr();
	raw();
	keypad(stdscr, true);
	noecho();
	start_color();
	use_default_colors();
	curs_set(0);
	init_pair(pair_blue, COLOR_BLUE, -1);
	init_pair(pair_red, COLOR_RED, -1);
	init_pair(pair_black, COLOR_BLACK, -1);
	init_pair(pair_yellow, COLOR_YELLOW, -1);
	init_pair(pair_green, COLOR_GREEN, -1);
}

void ncursesQuit()
{
	endwin();
}

