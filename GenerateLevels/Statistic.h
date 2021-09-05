//
//  Statistic.h
//  GenerateLevels
//
//  Created by Николай Протасов on 04.09.2021.
//

#ifndef Statistic_h
#define Statistic_h

#include <iostream>
#include <memory>
#include <tuple>
#include <chrono>

#include "GameField.h"
#include "IPlayer.h"

template<typename T>
using shared_ptr = std::shared_ptr<T>;

class Statistic
{
public:
    unsigned int LandWinCount = 0;
    unsigned int WaterWinCount = 0;
    unsigned int DeadHeatCount = 0;
    
    GameField mField;
    
    shared_ptr<IPlayer> mPlayer1;
    shared_ptr<IPlayer> mPlayer2;
    
    Statistic(const GameField& field, shared_ptr<IPlayer> player1, shared_ptr<IPlayer> player2):mPlayer1(player1), mPlayer2(player2), mField(field)
    {
        LandWinCount = 0;
        WaterWinCount = 0;
        DeadHeatCount = 0;
    }
    
    void Reset()
    {
        LandWinCount = 0;
        WaterWinCount = 0;
        DeadHeatCount = 0;
    }
    
    void CalculateStatistic(int samplesCount, CellType firstPlayer, bool printResult = false);
    void CalculateStatisticAsync(int samplesCount, CellType firstPlayer, bool printResult = false);
};


#endif /* Statistic_h */
