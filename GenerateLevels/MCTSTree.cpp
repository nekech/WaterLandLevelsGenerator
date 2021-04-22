#include <iostream>
#include "MCTSTree.h"

using namespace MCTS;

Tree::Tree(const GameField& field, CellType playerType, std::chrono::duration<int> duration) : playerType(playerType), duration(duration)
{
	root = std::make_shared<Node>(nullptr, field, Step(), playerType);
}


Step Tree::FindNextMove()
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();

	int iterationCount = 0;

	while (current - start < duration)
	{
		shared_ptr<Node> promisingNode = SelectPromisingNode();

		if (!promisingNode->field.IsEnd())
		{
			ExpandNode(promisingNode);
		}

		shared_ptr<Node> nodeToExplore = promisingNode;
		if (promisingNode->childs.size() > 0)
		{
			nodeToExplore = promisingNode->GetRandomChildNode();
		}

		CellType playResult = nodeToExplore->SimulateRandomPlayout();
		BackPropogation(nodeToExplore, playResult);

		current = std::chrono::system_clock::now();
		iterationCount++;
	}

	std::cout << "Itteration count: " << iterationCount << std::endl;

	return root->GetChildWithBestWinScore()->step;
}

shared_ptr<Node> Tree::SelectPromisingNode()
{
	shared_ptr<Node> node = root;

	while (node->childs.size() != 0)
	{
		node = FindBestNodeWithUCT(node);
	}

	return node;
}

void Tree::ExpandNode(shared_ptr<Node> node)
{
	node->ComputeChilds();
}

void Tree::BackPropogation(shared_ptr<Node> node, CellType winner)
{
	shared_ptr<Node> updateNode = node;

	while (updateNode != nullptr)
	{
		updateNode->visitCount++;

		if (updateNode->playerType == winner)
		{
			updateNode->UpdateWinScore();
		}

		updateNode = updateNode->parent.lock();
	}
}

shared_ptr<Node> Tree::FindBestNodeWithUCT(shared_ptr<Node> node)
{
	int parentVisitCount = node->visitCount;

	double maxUCT = DBL_MIN;
	shared_ptr<Node> maxNode;

	for (auto child : node->childs)
	{
		double nodeUCT = child->ComputeNodeUCT(parentVisitCount);

		if (nodeUCT > maxUCT)
		{
			maxUCT = nodeUCT;

			maxNode = child;
		}
	}

	return maxNode;
}