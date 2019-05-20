#ifndef State_h_
#define State_h_
#include <vector>
#include <cmath>
#include <limits>
#define INF INFINITY

enum Player { human, computer };

class State
{
protected:
	double h;
	Player whose_turn;
	State* root_move;
	State* parent;
	bool made_children;
	std::vector<State*> children;
	State(State* aobj);
	virtual void computeH() = 0;
	virtual void makeChildren() = 0;
public:
	State(Player awhose_turn);
	virtual bool isTerminal() = 0;
	double getH();
	State* getRootMove();
	Player getWhoseTurn();
	std::vector<State*> getChildren();
	void makeRoot();
	virtual void display() = 0;
	virtual ~State();
};

#endif

