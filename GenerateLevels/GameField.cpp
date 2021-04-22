#include "GameField.h"

#include <iostream>

GameField::GameField(int width, int height) : m_width(width), m_height(height)
{
	cells = new GameCell[m_width * m_height]();
}

GameField::GameField()
{
	cells = nullptr;
}

GameField::GameField(const GameField& field):m_width(field.m_width), m_height(field.m_height)
{
	cells = new GameCell[m_width * m_height];

	memcpy(cells, field.cells, m_width * m_height * sizeof(GameCell));
}

GameField GameField::Clone() const
{
	std::cout << "Gamefield clone" << std::endl;

	GameField ret(m_width, m_height);

	for (int i = 0; i < m_width * m_height; ++i)
	{
		ret.cells[i] = cells[i];
	}

	return ret;
}

GameCell& GameField::GetCell(int x, int y) const
{
	/*
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
	{
		std::cout << "error" << std::endl;
	}
	*/

	return cells[x * m_height + y];
}

GameCell& GameField::GetCell(Vector2<int> position) const
{
	/*
	if (position.x < 0 || position.x >= m_width || position.y < 0 || position.y >= m_height)
	{
		std::cout << "error" << std::endl;
	}
	*/

	return cells[position.x * m_height + position.y];
}

void GameField::SetCell(int x, int y, GameCell cell)
{
	GetCell(x, y).type = cell.type;
}

std::list<Step> GameField::GetAllPossibleSteps(CellType playerType) const
{
	std::list<Step> steps;

	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			if (GetCell(i, j).HasFlag(playerType))
			{
				auto cellSteps = GetPossibleSteps(Vector2<int>(i, j), 2);

				if (cellSteps.size() > 0)
				{
					steps.insert(steps.end(), cellSteps.begin(), cellSteps.end());
				}
			}
		}
	}

	return steps;
}

std::list<Step> GameField::GetPossibleSteps(Vector2<int> cellCoord, int level) const
{
	std::list<Step> steps;

	CellType constCellType = GetCell(cellCoord).HasFlag(CellType::LAND) ? CellType::CAVITY : CellType::ROCK;

	int leftBorder = cellCoord.x - level >= 0 ? cellCoord.x - level : 0;
	int rightBorder = cellCoord.x + level < m_width ? cellCoord.x + level : m_width - 1;

	int bottomBorder = cellCoord.y - level >= 0 ? cellCoord.y - level : 0;
	int topBorder = cellCoord.y + level < m_height ? cellCoord.y + level : m_height - 1;

	for (int i = leftBorder; i <= rightBorder; ++i)
	{
		for (int j = bottomBorder; j <= topBorder; ++j)
		{
			if (i == cellCoord.x && j == cellCoord.y)
			{
				continue;
			}

			if (GetCell(i, j).HasFlag(CellType::ICE) && !GetCell(i, j).HasFlag(constCellType))
			{
				steps.push_back(Step(cellCoord, Vector2<int>(i, j))); //TODO add check for long step
			}
		}
	}

	return steps;
}

void GameField::MakeMove(Step step)
{
	CellType newType = GetCell(step.from).HasFlag(CellType::LAND) ? CellType::LAND : CellType::WATER;

	GameCell& newCell = GetCell(step.to);
	newCell.type = newCell.type ^ CellType::ICE;

	if (newCell.HasFlag(CellType::ROCK) || newCell.HasFlag(CellType::CAVITY))
	{
		newCell.type = newCell.type | newType;
	}
	else
	{
		newCell.type = newType;
	}

	if ((abs(step.from.x - step.to.x) > 1 || abs(step.from.y - step.to.y) > 1))
	{
		if (GetCell(step.from).HasFlag(CellType::CAVITY))
		{
			GetCell(step.from).type = CellType::CAVITY | CellType::ICE;
		}
		else if (GetCell(step.from).HasFlag(CellType::ROCK))
		{
			GetCell(step.from).type = CellType::ROCK | CellType::ICE;
		}
		else
			GetCell(step.from).type = CellType::ICE;
	}

	auto tmp = GetCell(step.to);

	CaptureCells(step.to);
}

void GameField::CaptureCells(Vector2<int> newCell)
{
	CellType newType = GetCell(newCell).HasFlag(CellType::WATER) ? CellType::WATER : CellType::LAND;

	CellType enemyType = newType == CellType::WATER ? CellType::LAND : CellType::WATER;

	int leftBorder = newCell.x - 1 >= 0 ? newCell.x - 1 : 0;
	int rightBorder = newCell.x + 1 < m_width ? newCell.x + 1 : m_width - 1;

	int bottomBorder = newCell.y - 1 >= 0 ? newCell.y - 1 : 0;
	int topBorder = newCell.y + 1 < m_height ? newCell.y + 1 : m_height - 1;

	for (int i = leftBorder; i <= rightBorder; ++i)
	{
		for (int j = bottomBorder; j <= topBorder; ++j)
		{
			if (GetCell(i, j).type == enemyType)
			{
				GetCell(i, j).type = newType;
			}
		}
	}
}

void GameField::Print(bool printScale)
{
	for (int j = m_height - 1; j >= 0; --j)
	{
		if (printScale)
		{
			std::cout << j << "| ";
		}

		for (int i = 0; i < m_width; ++i)
		{
			GameCell cell = GetCell(i, j);

			switch (cell.type)
			{
			case CellType::ICE:
				std::cout << "I";
				break;
			case CellType::LAND:
				std::cout << "L";
				break;
			case CellType::WATER:
				std::cout << "W";
				break;
				/*
				case CellType::ROCK:
					std::cout << "R";
					break;
				case CellType::CAVITY:
					std::cout << "C";
					break;
				*/
			default:
				break;
			}

			if (cell.type == (CellType::ROCK | CellType::ICE)) //TODO do it in switch
			{
				std::cout << "R";
			}

			if (cell.type == (CellType::CAVITY | CellType::ICE))
			{
				std::cout << "C";
			}

			if (cell.type == (CellType::ROCK | CellType::LAND)) //TODO do it in switch
			{
				std::cout << "M";
			}

			if (cell.type == (CellType::CAVITY | CellType::WATER))
			{
				std::cout << "H";
			}

			std::cout << " ";
		}

		std::cout << std::endl;
	}

	if (printScale)
	{
		std::cout << " | ";
		for (int i = 0; i < m_width; ++i)
		{
			std::cout << i << " ";
		}

		std::cout << std::endl;
	}
}

int GameField::GetCellTypeCount(CellType type) const
{
	int count = 0;

	for (int i = 0; i < m_width * m_height; ++i)
	{
		if (cells[i].HasFlag(type))
			count++;
	}

	return count;
}

bool GameField::IsEnd() const
{
	auto waterPossibleSteps = GetAllPossibleSteps(CellType::WATER);
	auto landPossibleSteps = GetAllPossibleSteps(CellType::LAND);

	if (waterPossibleSteps.empty() || landPossibleSteps.empty())
		return true;

	return false;
}

GameField::~GameField()
{
	delete[] cells;
}