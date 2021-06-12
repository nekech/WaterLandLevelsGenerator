#include <cfloat>
#include <iostream>
#include "MCTSTree.h"

using namespace MCTS;

Tree::Tree(const GameField& field, CellType playerType, std::chrono::duration<int> duration) : playerType(playerType), duration(duration)
{
	root = std::make_shared<Node>(nullptr, field, Step(), playerType, playerType);
}


Step Tree::GetStep()
{
    maxDepth = 0;
    
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();

	int iterationCount = 0;

	while (current - start < duration)
    {
        shared_ptr<Node> selectedNode = Select(root);
        
        if (selectedNode == nullptr)
            break;
        
        GameResult simulationResult = selectedNode->RandomPlayout();
        totalVisitCount++;
        
        BackPropogation(selectedNode, simulationResult);
        
		current = std::chrono::system_clock::now();
		iterationCount++;
	}

	std::cout << "Itteration count: " << iterationCount << std::endl;
    std::cout << "Max Depth: " << maxDepth << std::endl;

	return root->GetChildWithBestUCTScore(totalVisitCount)->step;
}

void Tree::ExpandNode(shared_ptr<Node> node)
{
	node->ComputeChilds();
}

void Tree::BackPropogation(shared_ptr<Node> node, GameResult simulationResult)
{
	shared_ptr<Node> updateNode = node;

	while (updateNode != nullptr)
	{
		updateNode->visitCount++;

        updateNode->UpdateWinScore(simulationResult);

		updateNode = updateNode->parent.lock();
	}
}

shared_ptr<Node> Tree::Select(shared_ptr<Node> node, int currentDepth)
{
    if (currentDepth > maxDepth)
    {
        maxDepth = currentDepth;
    }
    
    if (node->field.IsEnd() || node->visitCount == 0)
    {
        return node;
    }
    
    if (node->childs.size() == 0)
    {
        node->ComputeChilds();
        
        return node->GetRandomChildNode();
    }
    
    double bestScore = -DBL_MAX;
    
    std::function<bool(double, double)> compareFunction = [](double a, double b) {return a > b; };
    
    if (node->nodePlayerType != playerType)
    {
        bestScore = DBL_MAX;
        
        compareFunction = [](double a, double b) { return a < b; };
    }
    
    shared_ptr<Node> bestNode = node->GetChildWithBestUCTScore(totalVisitCount, bestScore, compareFunction);
    
    return Select(bestNode, currentDepth + 1);
}
