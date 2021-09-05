#include <cfloat>
#include <math.h>

#include "MCTSNode.h"
#include "Game.h"
#include "RandomPlayer.h"
#include "GreedyPlayer.h"

using namespace MCTS;

Node::Node(shared_ptr<Node> parent, const GameField& field, Step step, CellType nodePlayerType, CellType playerType):  field(field), step(step), nodePlayerType(nodePlayerType), visitCount(0), winScore(0), playerType(playerType)
{
	this->parent = parent;
	if (parent != nullptr)
	{
		this->field.MakeMove(step);
        
        if (field.IsEnd())
        {
            isTerminal = true;
        }
	}

	nodeOpponentType = nodePlayerType == CellType::WATER ? CellType::LAND : CellType::WATER;
}

void Node::ComputeChilds()
{
	auto possibleSteps = field.GetAllPossibleSteps(nodePlayerType);

	for (auto possibleStep : possibleSteps)
	{
		childs.push_back(std::make_shared<Node>(shared_from_this(), field, possibleStep, nodeOpponentType, playerType)); //TODO debug pointer logic
	}
}

GameResult Node::RandomPlayout()
{
    GameResult result;
     
    if (isTerminal || true) //TODO remove true
    {
        result.WaterCount = field.GetCellTypeCount(CellType::WATER);
        result.LandCount = field.GetCellTypeCount(CellType::LAND);
        return result;
    }
    
	GameField tmpField(field);

	shared_ptr<IPlayer> player1(new RandomPlayer(nodePlayerType));
	shared_ptr<IPlayer> player2(new RandomPlayer(nodeOpponentType));
//	shared_ptr<IPlayer> player1(new GreedyPlayer(nodePlayerType));
//	shared_ptr<IPlayer> player2(new GreedyPlayer(nodeOpponentType));


	Game randomGame(tmpField, nodePlayerType, player1, player2);

	randomGame.Start();
	
    result.WaterCount = field.GetCellTypeCount(CellType::WATER);
    result.LandCount = field.GetCellTypeCount(CellType::LAND);
    
    return result;
}

std::shared_ptr<Node> Node::GetChildWithBestWinScore()
{
	double maxWinScore = childs.front()->winScore;
	shared_ptr<Node> maxNode = childs.front();

	for (auto child : childs)
	{
		if (child->winScore > maxWinScore)
		{
			maxWinScore = child->winScore;
			maxNode = child;
		}
	}

	return maxNode;
}

std::shared_ptr<Node> Node::GetChildWithBestUCTScore(int totalVisitCount)
{
    double maxUTCScore = 0;
    shared_ptr<Node> maxNode = nullptr;
    
    for (auto child : childs)
    {
        if (child->visitCount > 0)
        {
            maxUTCScore = child->GetUCTScore(totalVisitCount);
            maxNode = child;
            break;
        }
    }
    
    for (auto child : childs)
    {
        if (child->visitCount > 0 && child->GetUCTScore(totalVisitCount) > maxUTCScore)
        {
            maxUTCScore = child->winScore;
            maxNode = child;
        }
    }

    return maxNode;
}

std::shared_ptr<Node> Node::GetChildWithBestUCTScore(int totalVisitCount, double bestScore, std::function<bool(double, double)> compareFunction)
{
    std::list<shared_ptr<Node>> bestNodes;
    
    for (auto child : childs)
    {
        double childScore = child->GetUCTScore(totalVisitCount);
        
        if (compareFunction(childScore, bestScore))
        {
            bestNodes.clear();
            bestNodes.push_back(child);
            
            bestScore = childScore;
            
            continue;
        }
        
        if (childScore == bestScore)
        {
            bestNodes.push_back(child);
        }
    }
    
    if (bestNodes.size() == 1)
        return bestNodes.front();

    srand(clock());
    int randIndex = rand() % bestNodes.size();

    int  i = 0;
    for (auto it = bestNodes.begin(); it != bestNodes.end(); ++it)
    {
        if (i == randIndex)
        {
            return *it;
        }

        ++i;
    }

    return nullptr;
}

std::shared_ptr<Node> Node::GetRandomChildNode()
{
	if (childs.size() == 1)
		return childs.front();

	srand(clock());
	int randIndex = rand() % childs.size();

	int  i = 0;
	for (auto it = childs.begin(); it != childs.end(); ++it)
	{
		if (i == randIndex)
		{
			return *it;
		}

		++i;
	}

	return nullptr;
}

void Node::UpdateWinScore(GameResult result)
{
    if (playerType == CellType::WATER)
    {
        winScore += result.WaterCount;
        //winScore += result.WaterCount - result.LandCount;
        //winScore += result.WaterCount > result.LandCount ? 1 : 0;
    }
    else
    {
        winScore += result.LandCount;
        //winScore += result.LandCount - result.WaterCount;
        //winScore += result.LandCount > result.WaterCount ? 1 : 0;
    }
}

double Node::GetUCTScore(int totalVisitCount)
{
    if (visitCount == 0)
    {
        return DBL_MAX; //TODO replace with constant
    }
    
    return winScore/(double)visitCount + 1.41 * sqrt(log(totalVisitCount) / (double)(visitCount));
}

