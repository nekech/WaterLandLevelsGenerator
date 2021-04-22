#include "GameCell.h"

GameCell::GameCell(CellType type) :type(type)
{
}

GameCell::GameCell()
{}

bool GameCell::HasFlag(CellType flag)
{
	CellType tmp = type & flag;
	return (bool)tmp;
}