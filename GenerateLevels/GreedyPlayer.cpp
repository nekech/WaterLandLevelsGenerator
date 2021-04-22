#include <iostream>

#include "GreedyPlayer.h"

GreedyPlayer::GreedyPlayer(CellType playerType) :IPlayer(playerType)
{
}

Step GreedyPlayer::GetStep(const GameField& field)
{
	auto possibleSteps = field.GetAllPossibleSteps(playerType);

	std::vector<Step> maxSteps;
	int maxCount = 0;

	for (auto step : possibleSteps)
	{
		GameField tmpField(field);

		tmpField.MakeMove(step);

		int count = tmpField.GetCellTypeCount(playerType);

		if (count == maxCount)
		{
			maxSteps.push_back(step);
		}

		if (count > maxCount)
		{
			maxSteps.clear();
			maxSteps.push_back(step);

			maxCount = count;
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

