#ifndef MCTS_PLAYER
#define MCTS_PLAYER
#pragma once

#include "IPlayer.h"

class MCTSPlayer : public IPlayer
{
public:
    
    std::chrono::duration<int> duration;

	MCTSPlayer(CellType playerType, std::chrono::duration<int> duration = std::chrono::seconds(60));

	Step GetStep(const GameField& field);
};

#endif // !MCTS_PLAYER
