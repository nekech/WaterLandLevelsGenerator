#include "RandomPlayer.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

RandomPlayer::RandomPlayer(CellType playerType) :IPlayer(playerType)
{
}

Step RandomPlayer::GetStep(const GameField& field)
{
	auto possibleSteps = field.GetAllPossibleSteps(playerType);

	if (possibleSteps.empty())
		return Step();

	if (possibleSteps.size() == 1)
		return possibleSteps.front();

	srand(clock());
	int randIndex = rand() % possibleSteps.size();

	int  i = 0;
	for (auto it = possibleSteps.begin(); it != possibleSteps.end(); ++it)
	{
		if (i == randIndex)
		{
			return *it;
		}

		++i;
	}

	return Step();
}