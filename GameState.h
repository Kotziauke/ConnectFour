#ifndef GameState_h_
#define GameState_h_
#include <ncurses.h>
#include "State.h"

enum ColorPair { pair_default = 0, pair_human = 1, pair_computer = 2, pair_empty = 3, pair_cursor = 4 };

class GameState : public State
{
private:
	int width;
	int height;
	char** board;
	GameState(GameState* aobj, int acolumn);
	char getCell(int ax, int ay);
	void computeH() override;
	void makeChildren() override;
	void copyBoard(GameState* aobj);
public:
	GameState(Player awhose_turn, int awidth, int aheight);
	GameState* dropChecker(int acolumn);
	void display() override;
	~GameState();
};

#endif

