#include "MCTSPlayer.h"

#include "MCTSTree.h"

MCTSPlayer::MCTSPlayer(CellType playerType, std::chrono::duration<int> duration) :IPlayer(playerType), duration(duration)
{
}

Step MCTSPlayer::GetStep(const GameField& field)
{
	MCTS::Tree tree(field, playerType, duration);
	return tree.FindNextMove();
}
