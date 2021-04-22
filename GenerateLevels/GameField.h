#ifndef  GAME_FIELD
#define GAME_FIELD
#pragma once

#include <vector>
#include <list>

#include "GameCell.h"
#include "Step.h"


class GameField
{
public:
	int m_width;
	int m_height;

	GameCell* cells = nullptr;

	GameField(int width, int height);

	GameField(const GameField& field);

	GameField();

	GameField Clone() const;

	GameCell& GetCell(int x, int y) const;

	GameCell& GetCell(Vector2<int> position) const;

	void SetCell(int x, int y, GameCell cell);

	std::list<Step> GetAllPossibleSteps(CellType playerType) const;

	std::list<Step> GetPossibleSteps(Vector2<int> cellCoord, int level = 2) const;

	void MakeMove(Step step);

	void CaptureCells(Vector2<int> newCell);

	void Print(bool printScale = false);

	int GetCellTypeCount(CellType type) const;

	bool IsEnd() const;

	~GameField();
};

#endif // ! GAME_FIELD