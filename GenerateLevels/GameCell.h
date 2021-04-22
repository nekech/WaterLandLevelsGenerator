#ifndef GAME_CELL
#define GAME_CELL
#pragma once

#include "EnumBitOperations.h"

enum class CellType
{
	ICE = 2,
	LAND = 4,
	WATER = 8,
	ROCK = 16,
	CAVITY = 32
};

template<>
struct enable_bitmask_operators<CellType> {
	static constexpr bool enable = true;
};

class GameCell
{
public:
	CellType type = CellType::ICE;

	GameCell(CellType type);

	GameCell();

	bool HasFlag(CellType flag);
};

#endif // !GAME_CELL