#ifndef MCTS_TREE
#define MCTS_TREE
#pragma once

#include <chrono>

#include "MCTSNode.h"

namespace MCTS
{
	class Tree
	{
	public:
		shared_ptr<Node> root;

		std::chrono::duration<int> duration;

		CellType playerType;

		Tree(const GameField& field, CellType playerType, std::chrono::duration<int> duration = std::chrono::seconds(60));

		Step FindNextMove();

		shared_ptr<Node> FindBestNodeWithUCT(shared_ptr<Node> node);

		void ExpandNode(shared_ptr<Node> node);

		void BackPropogation(shared_ptr<Node> node, CellType winner);

		shared_ptr<Node> SelectPromisingNode();
	};
}

#endif // !MCTS_TREE
