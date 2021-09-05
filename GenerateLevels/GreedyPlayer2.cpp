#include "GreedyPlayer2.h"

#include "GreedyPlayer.h"

GreedyPlayer2::GreedyPlayer2(CellType playerType) :IPlayer(playerType)
{
    playerName = "Greedy Player2";
}

GreedyPlayer2::GreedyPlayer2(CellType playerType, IPlayer::ScoreFunction scoreFunction):IPlayer(playerType, scoreFunction)
{
    playerName = "Greedy Player2";
}

Step GreedyPlayer2::GetStep(const GameField& field)
{
	GreedyPlayer currentPlayer(playerType);
	GreedyPlayer opponentPlayer(playerType == CellType::LAND ? CellType::WATER : CellType::LAND);

	GameField tmpField(field);

	auto steps = tmpField.GetAllPossibleSteps(playerType);

	std::vector<Step> maxSteps;
	double maxScore = 0;
	
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
	
        double score = GetScore(stepField, playerType);

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
