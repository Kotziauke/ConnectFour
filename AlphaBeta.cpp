#include "AlphaBeta.h"

std::pair<double, State*> alphaBeta(State* aobj, double depth, double alpha, double beta)
{
	if (depth == 0.0 || aobj->isTerminal() == true)
	{
		return std::pair<double, State*>(aobj->getH(), aobj);
	}
	std::pair<double, State*> ret(0.0, NULL);
	switch (aobj->getWhoseTurn())
	{
	case computer: //gracz maksymalizujący
		ret.first = -INF;
		for (State* child : aobj->getChildren())
		{
			std::pair<double, State*> temp = alphaBeta(child, depth - 0.5, alpha, beta);
			if (ret.second == NULL || temp.first > ret.first)
			{
				ret = temp;
			}
			alpha = std::max(alpha, ret.first);
			if (alpha >= beta)
			{
				break;
			}
		}
		return ret;
	case human: //gracz minimalizujący
		ret.first = INF;
		for (State* child : aobj->getChildren())
		{
			std::pair<double, State*> temp = alphaBeta(child, depth - 0.5, alpha, beta);
			if (ret.second == NULL || temp.first < ret.first)
			{
				ret = temp;
			}
			beta = std::min(beta, ret.first);
			if (alpha >= beta)
			{
				break;
			}
		}
		return ret;
	}
}

