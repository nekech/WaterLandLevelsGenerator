#ifndef GREEDY_PLAYER_2
#define GREEDY_PLAYER_2
#pragma once

#include "IPlayer.h"

class GreedyPlayer2 : public IPlayer
{
public:

	GreedyPlayer2(CellType playerType);
    
    GreedyPlayer2(CellType playerType, IPlayer::ScoreFunction scoreFunction);

	Step GetStep(const GameField& field);
};

#endif // !GREEDY_PLAYER_2
