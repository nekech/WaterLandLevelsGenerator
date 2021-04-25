#ifndef I_PLAYER
#define I_PLAYER
#pragma once

#include <functional>

#include "GameField.h"

class IPlayer
{
public:
	CellType playerType;
    
    std::function<double(const GameField&, CellType)> GetScore = DefaultGetScore;
    
    IPlayer(const CellType& playerType) :playerType(playerType)
    {
    }

	IPlayer(const CellType& playerType, std::function<double(const GameField&, CellType)> getScore) :playerType(playerType)
	{
        GetScore = getScore;
	}

	virtual Step GetStep(const GameField& field) = 0;

	virtual ~IPlayer()
	{
	}
    
    static double DefaultGetScore(const GameField& field, CellType playerType)
    {
        return field.GetCellTypeCount(playerType);
    }
};

#endif // !I_PLAYER
