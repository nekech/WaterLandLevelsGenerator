#ifndef MINI_MAX_MODIFIED_PLAYER
#define MINI_MAX_MODIFIED_PLAYER
#pragma once

#include "IPlayer.h"

class MiniMaxModifiedPlayer : public IPlayer
{
public:

	int depth;

	MiniMaxModifiedPlayer(CellType playerType, int depth = 2);

	Step GetStep(const GameField& field);

	double GetStepScore(const GameField& field, int depth, bool max, CellType currentPlayer, double& result);

	void ReduceSameSteps(std::list<Step>& steps);
};

#endif // !MINI_MAX_MODIFIED_PLAYER
