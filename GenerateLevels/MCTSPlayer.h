#ifndef MCTS_PLAYER
#define MCTS_PLAYER
#pragma once

#include "IPlayer.h"

class MCTSPlayer : public IPlayer
{
public:

	MCTSPlayer(CellType playerType);

	Step GetStep(const GameField& field);
};

#endif // !MCTS_PLAYER
