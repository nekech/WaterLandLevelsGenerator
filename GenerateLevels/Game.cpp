#include <iostream>

#include "Game.h"

Game::Game(const GameField& field, CellType startPlayer, shared_ptr<IPlayer> playerOne, shared_ptr<IPlayer> playerTwo) :field(field), currentPlayer(startPlayer),
	playerOne(std::move(playerOne)), playerTwo(std::move(playerTwo))
{
}

void Game::Start(bool debug)
{
	while (true)
	{
		if (debug)
		{
			field.Print(true);
		}

		Step step;

		if (playerOne->playerType == currentPlayer)
		{
			step = playerOne->GetStep(field);
		}
		else
		{
			step = playerTwo->GetStep(field);
		}

		if (step.from == Vector2<int>(-1, -1))
		{
			break;
		}

		field.MakeMove(step);
		if (debug)
		{
			std::cout << step.from << " -> " << step.to << std::endl;
			std::cout << "Water: " << field.GetCellTypeCount(CellType::WATER) << " Land: " << field.GetCellTypeCount(CellType::LAND) << std::endl;
		}

		if (field.IsEnd())
		{
			break;
		}

		ChangePlayer();
	}

	if (debug)
	{
		field.Print(true);
	}
}

void Game::ChangePlayer()
{
	if (currentPlayer == CellType::WATER)
	{
		currentPlayer = CellType::LAND;
	}
	else
	{
		currentPlayer = CellType::WATER;
	}
}

CellType Game::GetWinner()
{
	int waterCount = field.GetCellTypeCount(CellType::WATER);
	int landCount = field.GetCellTypeCount(CellType::LAND);

	if (waterCount > landCount)
	{
		return CellType::WATER;
	}

	if (waterCount < landCount)
	{
		return CellType::LAND;
	}

	return CellType::ICE;
}