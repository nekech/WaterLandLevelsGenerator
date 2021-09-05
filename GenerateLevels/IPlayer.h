#ifndef I_PLAYER
#define I_PLAYER
#pragma once

#include <functional>

#include "GameField.h"

class IPlayer
{
public:
    
    typedef std::function<double(const GameField&, CellType)> ScoreFunction;
    
	CellType playerType;
    
    std::string playerName = "IPlayer";
    
    ScoreFunction GetScore = DefaultGetScore;
    
    IPlayer(const CellType& playerType) :playerType(playerType)
    {
    }

	IPlayer(const CellType& playerType, ScoreFunction getScore) :playerType(playerType)
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
