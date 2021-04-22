#include "MCTSPlayer.h"

#include "MCTSTree.h"

MCTSPlayer::MCTSPlayer(CellType playerType) :IPlayer(playerType)
{
}

Step MCTSPlayer::GetStep(const GameField& field)
{
	MCTS::Tree tree(field, playerType);
	return tree.FindNextMove();
}