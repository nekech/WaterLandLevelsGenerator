#include <cfloat>
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
        shared_ptr<Node> selectedNode = Select(root);
        
        CellType simulationResult = selectedNode->SimulateRandomPlayout();
        totalVisitCount++;
        
        BackPropogation(selectedNode, simulationResult);
        
		current = std::chrono::system_clock::now();
		iterationCount++;
	}

	std::cout << "Itteration count: " << iterationCount << std::endl;

	return root->GetChildWithBestWinScore()->step;
}

void Tree::ExpandNode(shared_ptr<Node> node)
{
	node->ComputeChilds();
}

void Tree::BackPropogation(shared_ptr<Node> node, CellType winner)
{
	shared_ptr<Node> updateNode = node;
    
    double updateScore = 1;
    
    if (node->isTerminal)
    {
        updateScore = DBL_MAX;
    }

	while (updateNode != nullptr)
	{
		updateNode->visitCount++;

        updateNode->UpdateWinScore(winner, updateScore);

		updateNode = updateNode->parent.lock();
	}
}

shared_ptr<Node> Tree::Select(shared_ptr<Node> node)
{
    if (node->field.IsEnd())
    {
        return node;
    }
    
    if (node->childs.size() == 0)
    {
        node->ComputeChilds();
        
        return node->GetRandomChildNode();
    }
    
    double bestScore = -1;
    
    shared_ptr<Node> bestNode = nullptr;
    
    for (auto child : node->childs)
    {
        double childScore = child->GetUCTScore(totalVisitCount);
        
        if (childScore > bestScore)
        {
            bestNode = child;
            
            bestScore = childScore;
        }
    }
    
        if (bestNode->visitCount > 0)
    {
        return Select(bestNode);
    }
    
    return bestNode;
}
