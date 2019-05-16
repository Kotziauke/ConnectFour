#ifndef Ncurses_h_
#define Ncurses_h_
#include <ncurses.h>

enum ColorPair { pair_default = 0, pair_blue = 1, pair_red = 2, pair_black = 3, pair_yellow = 4, pair_green = 5 };

void ncursesInit();
void ncursesQuit();

#endif

