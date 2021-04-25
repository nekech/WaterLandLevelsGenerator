#include <functional>
#include <list>
#include <thread>
#include <algorithm>

#include "MiniMaxPlayer.h"

MiniMaxPlayer::MiniMaxPlayer(CellType playerType, int depth) :IPlayer(playerType), depth(depth)
{
}

Step MiniMaxPlayer::GetStep(const GameField& field) //TODO add threads
{
	auto steps = field.GetAllPossibleSteps(playerType);

	ReduceSameSteps(steps);

	CellType nextPlayer = playerType == CellType::WATER ? CellType::LAND : CellType::WATER;

	double bestScore = -1;
	std::list<Step> bestSteps;

	double a = -1 * field.m_height * field.m_width; //TODO replace to depends from heuristic function
	double b = 2 * field.m_height * field.m_width; //TODO replace to depends from heuristic function

	int i = 0;
	for (auto step : steps)
	{
		GameField tmpField(field);
		tmpField.MakeMove(step);

		double stepScore = GetStepScore(tmpField, depth - 1, false, nextPlayer, a, b);

		if (stepScore >= bestScore)
		{
			if (stepScore > bestScore)
			{
				bestSteps.clear();
			}

			bestScore = stepScore;

			bestSteps.push_back(step);
		}

		i++;
	}

	return ChooseRandomStep(bestSteps);
}

double MiniMaxPlayer::GetStepScore(const GameField& field, int currentDepth, bool max, CellType currentPlayer, double a, double b)
{
	if (field.IsEnd() || currentDepth <= 0)
	{
		return GetScore(field, currentPlayer);
	}
	
	auto steps = field.GetAllPossibleSteps(currentPlayer);

	ReduceSameSteps(steps);

	double bestScore = -1;

	std::function<bool(double, double)> compareFunction = [](double a, double b) {return a > b; };

	std::function<void(double)> pruningFunction = [&a](double value) { a = std::max(a, value); };

	if (!max)
	{
		bestScore = field.m_width * field.m_height  + 1;

		compareFunction = [](double a, double b) {return a < b; };

		pruningFunction = [&b](double value) { b = std::min(b, value); };
	}

	CellType nextPlayer = currentPlayer == CellType::WATER ? CellType::LAND : CellType::WATER;

	for (auto step : steps)
	{
		GameField tmp(field);
		tmp.MakeMove(step);

		double stepScore = GetStepScore(tmp, currentDepth - 1, !max, nextPlayer, a, b);

		if (compareFunction(stepScore, bestScore))
		{
			bestScore = stepScore;
		}

		pruningFunction(stepScore);

		if (a >= b)
			break;
	}

	return bestScore;
}

void MiniMaxPlayer::ReduceSameSteps(std::list<Step>& steps)
{
	std::list<Vector2<int>> targets;

	for (auto it = steps.begin(); it != steps.end();)
	{
		if ((abs(it->from.x - it->to.x) > 1 || abs(it->from.y - it->to.y) > 1))
		{
			it++;
		}
		else
		{
			if (std::find(targets.begin(), targets.end(), it->to) != targets.end())
			{
				it = steps.erase(it);
			}
			else
			{
				targets.push_back(it->to);

				it++;
			}
		}
	}
}

Step MiniMaxPlayer::ChooseRandomStep(const std::list<Step>& steps)
{
	if (steps.size() == 0)
		return Step();

	if (steps.size() == 1)
		return steps.front();

	srand(clock());
	int randIndex = rand() % steps.size();

	int  i = 0;
	for (auto it = steps.begin(); it != steps.end(); ++it)
	{
		if (i == randIndex)
		{
			return *it;
		}

		++i;
	}

	return Step();
}
