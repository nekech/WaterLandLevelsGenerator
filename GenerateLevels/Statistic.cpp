//
//  Statistic.cpp
//  GenerateLevels
//
//  Created by Николай Протасов on 04.09.2021.
//

#include "Statistic.h"

#include "Game.h"

#include "ThreadPool.h"

void Statistic::CalculateStatistic(int samplesCount, CellType firstPlayer, bool printResult)
{
    auto t0 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < samplesCount; ++i)
    {
        Game game(mField, firstPlayer, mPlayer1, mPlayer2);
        game.Start();

        CellType winner = game.GetWinner();
        if (winner == CellType::WATER)
        {
            WaterWinCount++;
        }
        if (winner == CellType::LAND)
        {
            LandWinCount ++;
        }

        if (winner == CellType::ICE)
        {
           DeadHeatCount++;
        }
    }
    
    auto t1 = std::chrono::high_resolution_clock::now();
    
    if (printResult)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Water: " << WaterWinCount << " | " << "Land: " << LandWinCount << " | " << "Dead Heat: " <<DeadHeatCount << std::endl;
        std::cout << "duration: " << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() << std::endl;
    }
}

void Statistic::CalculateStatisticAsync(int samplesCount, CellType firstPlayer, bool printResult)
{
    int threadsCount = std::thread::hardware_concurrency();
    if (threadsCount == 0)
        threadsCount = 2;
    
    ThreadPool pool(threadsCount);
    std::vector< std::future<CellType> > results;
    
    auto t0 = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < samplesCount; ++i)
    {
        results.emplace_back(pool.enqueue([this, firstPlayer]
        {
            Game game(mField, firstPlayer, mPlayer1, mPlayer2);
            game.Start();
            
            return game.GetWinner();
        }));
    }
    
    for(auto && result: results)
    {
        CellType winner = result.get();
        
        if (winner == CellType::WATER)
        {
            WaterWinCount++;
        }
        if (winner == CellType::LAND)
        {
            LandWinCount ++;
        }

        if (winner == CellType::ICE)
        {
           DeadHeatCount++;
        }
    }
    
    if (printResult)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Water: " << WaterWinCount << " | " << "Land: " << LandWinCount << " | " << "Dead Heat: " <<DeadHeatCount << std::endl;
        std::cout << "duration: " << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() << std::endl;
    }
}
