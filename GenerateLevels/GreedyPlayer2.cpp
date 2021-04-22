#include "GreedyPlayer2.h"

#include "GreedyPlayer.h"

GreedyPlayer2::GreedyPlayer2(CellType playerType) :IPlayer(playerType)
{
}

Step GreedyPlayer2::GetStep(const GameField& field)
{
	GreedyPlayer currentPlayer(playerType);
	GreedyPlayer opponentPlayer(playerType == CellType::LAND ? CellType::WATER : CellType::LAND);

	GameField tmpField(field);

	auto steps = tmpField.GetAllPossibleSteps(playerType);

	std::vector<Step> maxSteps;
	int maxCount = 0;
	
	for (auto step : steps)
	{
		GameField stepField(tmpField);

		stepField.MakeMove(step);

		if (!stepField.IsEnd())
		{
			Step opponentStep = opponentPlayer.GetStep(stepField);

			stepField.MakeMove(opponentStep);

			if (!stepField.IsEnd())
			{
				Step nextStep = currentPlayer.GetStep(stepField);

				stepField.MakeMove(nextStep);
			}
		}
	
		int count = stepField.GetCellTypeCount(playerType);

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
