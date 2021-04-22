#ifndef I_PLAYER
#define I_PLAYER
#pragma once

#include "GameField.h"

class IPlayer
{
public:
	CellType playerType;

	IPlayer(const CellType& playerType) :playerType(playerType)
	{
	}

	virtual Step GetStep(const GameField& field) = 0;

	virtual ~IPlayer()
	{
	}
};

#endif // !I_PLAYER
