#ifndef MCTS_NODE
#define MCTS_NODE

#include "GameField.h"

namespace MCTS
{
	template<class T>
	using shared_ptr = std::shared_ptr<T>;

	struct Node : public std::enable_shared_from_this<Node>
	{
		GameField field;

		Step step;

		CellType playerType;
		CellType opponentType;

		int visitCount;

		double winScore;

		std::weak_ptr<Node> parent;

		std::list<shared_ptr<Node>> childs;

		Node(shared_ptr<Node> parent, const GameField& field, Step step, CellType playerType);

		void ComputeChilds();

		CellType SimulateRandomPlayout();

		double ComputeNodeUCT(int totalVisit);

		shared_ptr<Node> GetChildWithBestWinScore();

		shared_ptr<Node> GetRandomChildNode();

		void UpdateWinScore();
	};
}

#endif // !MCTS_NODE
