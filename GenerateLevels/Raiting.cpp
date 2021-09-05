//
//  Raiting.cpp
//  GenerateLevels
//
//  Created by Николай Протасов on 04.09.2021.
//
#include <fstream>

#include "Raiting.h"

void Raiting::ComputeRaiting(std::string fileName)
{
    std::vector<IPlayer> sortedPlayers;
    
    auto comparator = [this, fileName](const shared_ptr<IPlayer>& player1, const shared_ptr<IPlayer>& player2)
    {
        player1->playerType = CellType::WATER;
        player2->playerType = CellType::LAND;
        
        Statistic statistic(mGameField, player1, player2);
        statistic.CalculateStatisticAsync(mSamplesCount, player1->playerType);
        
        if (!fileName.empty())
        {
            std::ofstream outputFile;
            outputFile.open (fileName, std::ios::out | std::ios::app);
            
            outputFile<<player1->playerName << " VS "<<player2->playerName<<std::endl;
            outputFile<< statistic.WaterWinCount << " | " <<statistic.LandWinCount<<std::endl;
            outputFile <<"Dead head: "<<statistic.DeadHeatCount<<std::endl;
            
            outputFile.close();
            
            std::cout<<player1->playerName << " VS "<<player2->playerName<<std::endl;
            std::cout<< statistic.WaterWinCount << " | " <<statistic.LandWinCount<<std::endl;
            std::cout <<"Dead head: "<<statistic.DeadHeatCount<<std::endl;
        }
        
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

void Raiting::SaveToFile(std::string fileName)
{
    std::ofstream outputFile;
    outputFile.open (fileName, std::ios::out | std::ios::app);
    
    for(auto& player : mPlayers)
    {
        outputFile<<player->playerName<<std::endl;
    }
    
    outputFile.close();
}
