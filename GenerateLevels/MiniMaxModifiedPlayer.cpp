#include "MiniMaxModifiedPlayer.h"

#include <functional>
#include <list>
#include <thread>
#include <algorithm>
#include <cfloat>

MiniMaxModifiedPlayer::MiniMaxModifiedPlayer(CellType playerType, int depth) :IPlayer(playerType), depth(depth)
{
}

Step MiniMaxModifiedPlayer::GetStep(const GameField& field) //TODO add threads
{
	auto steps = field.GetAllPossibleSteps(playerType);

	ReduceSameSteps(steps);

	CellType nextPlayer = playerType == CellType::WATER ? CellType::LAND : CellType::WATER;

	double bestScore = -DBL_MAX;
	Step bestStep;

	std::vector<double> stepScores(steps.size(), 0);
	std::vector<std::thread> threads(steps.size());

	int i = 0;
	for (auto step : steps)
	{
		GameField tmpField(field);
		tmpField.MakeMove(step);

		threads[i] = std::thread([this, nextPlayer, tmpField, stepScores, i] {GetStepScore(tmpField, depth - 1, false, nextPlayer, (double&)stepScores[i]); });
		i++;
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	i = 0;
	for (auto step : steps)
	{
		if (stepScores[i] > bestScore)
		{
			bestScore = stepScores[i];

			bestStep = step;
		}
		i++;
	}

	return bestStep;
}

double MiniMaxModifiedPlayer::GetStepScore(const GameField& field, int currentDepth, bool max, CellType currentPlayer, double& result)
{
	if (field.IsEnd())
	{
		return field.GetCellTypeCount(playerType);
	}

	if (currentDepth != 0)
	{
		auto steps = field.GetAllPossibleSteps(currentPlayer);

		ReduceSameSteps(steps);

		double bestScore = -DBL_MAX;

		std::function<bool(double, double)> compareFunction = [](double a, double b) {return a > b; };

		if (!max)
		{
			bestScore = DBL_MAX;

			compareFunction = [](double a, double b) {return a < b; };
		}

		CellType nextPlayer = currentPlayer == CellType::WATER ? CellType::LAND : CellType::WATER;

		for (auto step : steps)
		{
			GameField tmp(field);
			tmp.MakeMove(step);

			double stepScore;

			GetStepScore(field, currentDepth - 1, !max, nextPlayer, stepScore);

			if (compareFunction(stepScore, bestScore))
			{
				bestScore = stepScore;
			}
		}

		result = bestScore;

		return bestScore;
	}
	else
	{
		return field.GetCellTypeCount(playerType);
	}

	return 0;
}

void MiniMaxModifiedPlayer::ReduceSameSteps(std::list<Step>& steps)
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
