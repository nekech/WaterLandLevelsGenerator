#ifndef  GREEDY_PLAYER
#define GREEDY_PLAYER

#include "IPlayer.h"

class GreedyPlayer : public IPlayer
{
public:

	GreedyPlayer(CellType playerType);

	Step GetStep(const GameField& field);
};

#pragma once
#endif // ! GREEDY_PLAYER
