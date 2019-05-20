#ifndef GameState_h_
#define GameState_h_
#include "State.h"
#include "Ncurses.h"

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
	bool isTerminal() override;
	GameState* dropChecker(int acolumn);
	void display() override;
	void displayWithCursor(int acolumn, const char* amsg);
	~GameState();
};

#endif

