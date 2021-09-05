//
//  Raiting.cpp
//  GenerateLevels
//
//  Created by Николай Протасов on 04.09.2021.
//

#include "Raiting.h"

void Raiting::ComputeRaiting()
{
    std::vector<IPlayer> sortedPlayers;
    
    auto comparator = [this](const shared_ptr<IPlayer>& player1, const shared_ptr<IPlayer>& player2)
    {
        player1->playerType = CellType::WATER;
        player2->playerType = CellType::LAND;
        
        Statistic statistic(mGameField, player1, player2);
        statistic.CalculateStatisticAsync(mSamplesCount, player1->playerType);
        
        return statistic.WaterWinCount < statistic.LandWinCount;
    };
    
    std::sort(mPlayers.begin(), mPlayers.end(), comparator);
}

void Raiting::PrintRaiting()
{
    for(auto& player : mPlayers)
    {
        std::cout<<player->playerName<<std::endl;
    }
}
