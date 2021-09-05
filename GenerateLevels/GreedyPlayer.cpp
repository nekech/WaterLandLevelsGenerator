#include <iostream>

#include "GreedyPlayer.h"

GreedyPlayer::GreedyPlayer(CellType playerType) :IPlayer(playerType)
{
    playerName = "Greedy Player";
}

Step GreedyPlayer::GetStep(const GameField& field)
{
	auto possibleSteps = field.GetAllPossibleSteps(playerType);

	std::vector<Step> maxSteps;
	double maxScore = 0;

	for (auto step : possibleSteps)
	{
		GameField tmpField(field);

		tmpField.MakeMove(step);

        double score = GetScore(tmpField, playerType);

		if (score == maxScore)
		{
			maxSteps.push_back(step);
		}

		if (score > maxScore)
		{
			maxSteps.clear();
			maxSteps.push_back(step);

			maxScore = score;
		}
	}

	if (maxSteps.size() == 1)
		return maxSteps[0];

	if (maxSteps.size() == 0)
		return Step();

	srand(clock());
	int randIndex = rand() % maxSteps.size();

	return maxSteps[randIndex];
}

