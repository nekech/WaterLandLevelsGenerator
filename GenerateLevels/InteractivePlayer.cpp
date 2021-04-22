#include <iostream>

#include "InteractivePlayer.h"

InteractivePlayer::InteractivePlayer(CellType playerType) :IPlayer(playerType)
{
}

Step InteractivePlayer::GetStep(const GameField& field)
{
	return InputStep();
}

Step InteractivePlayer::InputStep()
{
	int x, y;

	std::cout << "input from cell" << std::endl;
	std::cin >> x >> y;

	Vector2<int> from(x, y);

	std::cout << "input to cell" << std::endl;
	std::cin >> x >> y;

	Vector2<int> to(x, y);

	return Step(from, to);
}