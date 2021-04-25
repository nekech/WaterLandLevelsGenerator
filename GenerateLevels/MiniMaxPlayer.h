#ifndef MINIMAX_PLAYER
#define MINIMAX_PLAYER
#pragma once
#include <tuple>

#include "IPlayer.h"

class MiniMaxPlayer : public IPlayer
{
public:

	int depth;

	MiniMaxPlayer(CellType playerType, int depth = 2);

	Step GetStep(const GameField& field);

	double GetStepScore(const GameField& field, int depth, bool max, CellType currentPlayer, double a, double b);

	void ReduceSameSteps(std::list<Step>& steps);

	Step ChooseRandomStep(const std::list<Step>& steps);
};

#endif // !MINIMAX_PLAYER
