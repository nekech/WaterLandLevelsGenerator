//
//  GenerateRaiting.h
//  GenerateLevels
//
//  Created by Николай Протасов on 03.09.2021.
//

#ifndef GenerateRaiting_h
#define GenerateRaiting_h

#include <iostream>

#include <vector>

#include "Statistic.h"

template<typename T>
using shared_ptr = std::shared_ptr<T>;

class Raiting
{
public:
    
    GameField mGameField;
    
    std::vector<shared_ptr<IPlayer>> mPlayers;
    
    int mSamplesCount = 100;
    
    Raiting(const GameField& gameField, int samplesCount = 100): mGameField(gameField), mSamplesCount(samplesCount)
    {
    }
    
    void AddPlayer(shared_ptr<IPlayer> player)
    {
        mPlayers.push_back(player);
    }
    
    void ComputeRaiting();
    
    void PrintRaiting();
};

#endif /* GenerateRaiting_h */
