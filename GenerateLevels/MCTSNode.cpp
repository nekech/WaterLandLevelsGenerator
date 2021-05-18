#include <cfloat>
#include <math.h>

#include "MCTSNode.h"
#include "Game.h"
#include "RandomPlayer.h"
#include "GreedyPlayer.h"

using namespace MCTS;

Node::Node(shared_ptr<Node> parent, const GameField& field, Step step, CellType playerType):  field(field), step(step), playerType(playerType), visitCount(0), winScore(0)
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

	opponentType = playerType == CellType::WATER ? CellType::LAND : CellType::WATER;
}

void Node::ComputeChilds()
{
	auto possibleSteps = field.GetAllPossibleSteps(playerType);

	for (auto possibleStep : possibleSteps)
	{
		childs.push_back(std::make_shared<Node>(shared_from_this(), field, possibleStep, opponentType)); //TODO debug pointer logic
	}
}

CellType Node::SimulateRandomPlayout()
{
    if (isTerminal)
    {
        if (field.GetCellTypeCount(playerType) > field.GetCellTypeCount(opponentType))
        {
            return playerType;
        }
        else
        {
            return opponentType;
        }
    }
    
	GameField tmpField(field);

	shared_ptr<IPlayer> player1(new RandomPlayer(playerType));
	shared_ptr<IPlayer> player2(new RandomPlayer(opponentType));
	//shared_ptr<IPlayer> player1(new GreedyPlayer(playerType));
	//shared_ptr<IPlayer> player2(new GreedyPlayer(opponentType));


	Game randomGame(field, playerType, player1, player2);

	randomGame.Start();

	if (randomGame.GetWinner() == opponentType)
	{
		//winScore = DBL_MIN;
	}

	return randomGame.GetWinner();
}

double Node::ComputeNodeUCT(int totalVisit)
{
	if (visitCount == 0)
	{
		return DBL_MAX;
	}

	return (winScore / (double)visitCount) + 1.41 * sqrt(log(totalVisit) / (double)visitCount);
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

void Node::UpdateWinScore(CellType winner, double updateScore)
{
    if (winner == playerType)
        winScore += updateScore;
    else
        winScore -= updateScore;
}

double Node::GetUCTScore(int totalVisitCount)
{
    if (visitCount == 0)
    {
        return -DBL_MAX; //TODO replace with constant
    }

    return (winScore / (double)visitCount) + 1.41 * sqrt(log(totalVisitCount) / (double)visitCount);
}

