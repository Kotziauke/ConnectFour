#ifndef AlphaBeta_h_
#define AlphaBeta_h_
#include <utility>
#include "State.h"

std::pair<double, State*> alphaBeta(State* aobj, double depth, double alpha, double beta);

#endif

