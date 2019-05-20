#include "GameState.h"

GameState::GameState(Player awhose_turn, int awidth, int aheight) :
	State::State{ awhose_turn },
	width{ awidth },
	height{ aheight }
{
	board = new char*[width];
	for (int x = 0; x < width; x++)
	{
		board[x] = new char[height];
		for (int y = 0; y < height; y++)
		{
			board[x][y] = '.';
		}
	}
}

GameState::GameState(GameState* aobj, int acolumn) :
	State::State{ aobj },
	width{ aobj->width },
	height{ aobj->height }
{
	copyBoard(aobj);
	for (int y = height - 1;; y--)
	{
		if (board[acolumn][y] == '.')
		{
			if (whose_turn == human) //gracze zostali już zamienieni w konstruktorze State::State(State* aobj), dlatego te symbole są na odwrót!
			{
				board[acolumn][y] = 'x';
			}
			else
			{
				board[acolumn][y] = 'o';
			}
			break;
		}
	}
}

bool GameState::isTerminal()
{
	if (getH() == -INFINITY || getH() == INFINITY || getChildren().empty() == true)
	{
		return true;
	}
	return false;
}

void GameState::copyBoard(GameState* aobj)
{
	board = new char*[width];
	for (int x = 0; x < width; x++)
	{
		board[x] = new char[height];
		for (int y = 0; y < height; y++)
		{
			board[x][y] = aobj->board[x][y];
		}
	}
}

char GameState::getCell(int ax, int ay)
{
	if (ax < 0 || ax >= width || ay < 0 || ay >= height)
	{
		return '?';
	}
	else
	{
		return board[ax][ay];
	}
}

void GameState::computeH()
{
	h = 0.0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				for (int dx = -1; dx <= 1; dx++)
				{
					if (dx == 0 && dy == 0)
					{
						continue;
					}
					char buf[5];
					buf[1] = board[x][y];
					if (buf[1] != 'o' && buf[1] != 'x')
					{
						continue;
					}
					buf[0] = getCell(x - dx, y - dy);
					if (buf[0] == buf[1])
					{
						continue;
					}
					buf[2] = getCell(x + dx, y + dy);
					buf[3] = getCell(x + 2 * dx, y + 2 * dy);
					buf[4] = getCell(x + 3 * dx, y + 3 * dy);
					int len = 1;
					while (len < 4 && buf[1 + len] == buf[1])
					{
						len++;
					}
					switch (len)
					{
					case 1:
						h += buf[1] == 'o' ? -1 : 1;
						break;
					case 2:
						h += buf[1] == 'o' ? -16 : 16;
						break;
					case 3:
						h += buf[1] == 'o' ? -512 : 512;
						break;
					case 4:
						h = buf[1] == 'o' ? -INFINITY : INFINITY;
						return;
					}
				}
			}
		}
	}
}

GameState* GameState::dropChecker(int acolumn)
{
	if (board[acolumn][0] != '.')
	{
		return NULL;
	}
	else
	{
		return new GameState{ this, acolumn };
	}
}

void GameState::makeChildren()
{
	for (int x = 0; x < width; x++)
	{
		if (board[x][0] == '.')
		{
			new GameState{ this, x }; //jego konstruktor dopisze się do listy dzieci
		}
	}
}

void GameState::display()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (board[x][y])
			{
			case 'o':
				attrset(COLOR_PAIR(pair_blue) | A_BOLD);
				printw("o");
				break;
			case 'x':
				attrset(COLOR_PAIR(pair_red) | A_BOLD);
				printw("x");
				break;
			case '.':
				attrset(COLOR_PAIR(pair_black) | A_BOLD);
				printw(".");
				break;
			}
			attrset(COLOR_PAIR(pair_default));
		}
		printw("\n");
	}
}

void GameState::displayWithCursor(int acolumn)
{
	erase();
	for (int i = acolumn; i > 0; i--)
	{
		printw(" ");
	}
	attrset(COLOR_PAIR(pair_yellow) | A_BOLD);
	printw("V\n");
	attrset(COLOR_PAIR(pair_default));
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (board[x][y])
			{
			case 'o':
				attrset(COLOR_PAIR(pair_blue) | A_BOLD);
				printw("o");
				break;
			case 'x':
				attrset(COLOR_PAIR(pair_red) | A_BOLD);
				printw("x");
				break;
			case '.':
				if (x == acolumn)
				{
					attrset(COLOR_PAIR(pair_yellow) | A_BOLD);
					printw(":");
				}
				else
				{
					attrset(COLOR_PAIR(pair_black) | A_BOLD);
					printw(".");
				}
				break;
			}
			attrset(COLOR_PAIR(pair_default));
		}
		printw("\n");
	}
}

GameState::~GameState()
{
	for (int x = 0; x < width; x++)
	{
		delete board[x];
	}
	delete[] board;
}

