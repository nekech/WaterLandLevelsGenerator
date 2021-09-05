#include "MCTSPlayer.h"

#include "MCTSTree.h"

MCTSPlayer::MCTSPlayer(CellType playerType, std::chrono::duration<int> duration) :IPlayer(playerType), duration(duration)
{
    playerName = "MCTS Player " + std::to_string(duration.count());
}

Step MCTSPlayer::GetStep(const GameField& field)
{
	MCTS::Tree tree(field, playerType, duration);
	return tree.GetStep();
}
