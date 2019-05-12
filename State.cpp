#include "State.h"

State::State(Player awhose_turn) :
	h{ NAN },
	whose_turn{ awhose_turn },
	root_move{ NULL },
	parent{ NULL },
	made_children{ false }
{
}

State::State(State* aobj) :
	h{ NAN },
	whose_turn{ aobj->whose_turn == human ? computer : human },
	root_move{ aobj->root_move == NULL ? this : aobj->root_move },
	parent{ aobj },
	made_children{ false }
{
	aobj->children.push_back(this);
}

double State::getH()
{
	if (std::isnan(h))
	{
		computeH();
	}
	return h;
}

State* State::getRootMove()
{
	return root_move;
}

Player State::getWhoseTurn()
{
	return whose_turn;
}

std::vector<State*> State::getChildren()
{
	if (made_children == false)
	{
		makeChildren();
	}
	return children;
}

void State::makeRoot()
{
	root_move = NULL;
	parent = NULL;
}

State::~State()
{
	for(State* child : children)
	{
		delete child;
	}
}

