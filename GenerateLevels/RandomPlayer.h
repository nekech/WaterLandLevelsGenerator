#ifndef RANDOM_PLAYER
#define RANDOM_PLAYER
#pragma once

#include "IPlayer.h"

class RandomPlayer : public IPlayer
{
public:

	RandomPlayer(CellType playerType);

	Step GetStep(const GameField& field);
};

#endif // !RANDOM_PLAYER
