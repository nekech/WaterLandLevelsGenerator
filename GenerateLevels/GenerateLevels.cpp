// GenerateLevels.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <tuple>
#include <chrono>

#include "ThreadPool.h"

#include "GameField.h"
#include "Game.h"
#include "IPlayer.h"
#include "InteractivePlayer.h"
#include "RandomPlayer.h"
#include "GreedyPlayer.h"
#include "GreedyPlayer2.h"
#include "MiniMaxPlayer.h"
#include "MCTSPlayer.h"

template<typename T>
using shared_ptr = std::shared_ptr<T>;

struct RunStatistic
{
    unsigned int LandWinCount = 0;
    unsigned int WaterWinCount = 0;
    unsigned int DeadHeatCount = 0;
};

RunStatistic GetStatistic(int samplesCount, const GameField& field, shared_ptr<IPlayer> player1, shared_ptr<IPlayer> player2, CellType firstPlayer, bool printStatistic = false, bool debug = false)
{
    RunStatistic res;
    
    int threadsCount = std::thread::hardware_concurrency();
    if (threadsCount == 0)
        threadsCount = 2;

    auto t0 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < samplesCount; ++i)
    {
        Game game(field, firstPlayer, player1, player2);
        game.Start(debug);

        CellType winner = game.GetWinner();
        if (winner == CellType::WATER)
        {
            res.WaterWinCount++;
        }
        if (winner == CellType::LAND)
        {
            res.LandWinCount ++;
        }

        if (winner == CellType::ICE)
        {
           res.DeadHeatCount++;
        }
        
        if (printStatistic && false)
        {
            std::cout<<"Game number: "<<i<<" Winner: "<<(winner == CellType::WATER ? "water" : "land")<<std::endl;
        }
    }

    if (printStatistic)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Water: " << res.WaterWinCount << " | " << "Land: " << res.LandWinCount << " | " << "Dead Heat: " << res.DeadHeatCount << std::endl;
        std::cout << "duration: " << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() << std::endl;
    }

    return res;
}

void GetStatisticAsync(int samplesCount, const GameField& field, shared_ptr<IPlayer> player1, shared_ptr<IPlayer> player2, CellType firstPlayer, bool printStatistic = false, bool debug = false)
{
    int threadsCount = std::thread::hardware_concurrency();
    if (threadsCount == 0)
        threadsCount = 2;
    
    ThreadPool pool(threadsCount);
    std::vector< std::future<CellType> > results;
    
    auto t0 = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < samplesCount; ++i)
    {
        results.emplace_back(pool.enqueue([field, firstPlayer, player1, player2, debug]
        {
            Game game(field, firstPlayer, player1, player2);
            game.Start(debug);
            
            return game.GetWinner();
        }));
    }
    
    RunStatistic res;
    
    for(auto && result: results)
    {
        CellType winner = result.get();
        
        if (winner == CellType::WATER)
        {
            res.WaterWinCount++;
        }
        if (winner == CellType::LAND)
        {
            res.LandWinCount ++;
        }

        if (winner == CellType::ICE)
        {
           res.DeadHeatCount++;
        }
    }
    
    if (printStatistic)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Water: " << res.WaterWinCount << " | " << "Land: " << res.LandWinCount << " | " << "Dead Heat: " << res.DeadHeatCount << std::endl;
        std::cout << "duration: " << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count() << std::endl;
    }
    
}

void test()
{
    ThreadPool pool(4);
        std::vector< std::future<int> > results;

        for(int i = 0; i < 8; ++i) {
            results.emplace_back(
                pool.enqueue([i] {
                    std::cout << "hello " << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    std::cout << "world " << i << std::endl;
                    return i*i;
                })
            );
        }
    
    int sum = 0;

        for(auto && result: results)
        {
            int val =result.get();
            std::cout << val<< ' ';
            sum += val;
        }
        std::cout << std::endl;
    
    std::cout<<"Sum: "<<sum<<std::endl;
}

void RunInteractiveGame(const GameField& field, CellType firstPlayer, shared_ptr<IPlayer> aiPlayer)
{
    shared_ptr<IPlayer> humanPlayer(new InteractivePlayer(aiPlayer->playerType == CellType::WATER ? CellType::LAND : CellType::WATER));

    Game game(field, firstPlayer, humanPlayer, aiPlayer);
    game.Start(true);

    std::cout << "END" << std::endl;

    CellType winner = game.GetWinner();
    if (winner == CellType::WATER)
    {
        std::cout << "Water win" << std::endl;
    }
    if (winner == CellType::LAND)
    {
        std::cout << "Land wind" << std::endl;
    }

    if (winner == CellType::ICE)
    {
        std::cout << "Dead heat" << std::endl;
    }
}

void DebugMiniMax()
{
    GameField field(6, 6);
    field.SetCell(0, 0, CellType::WATER);
    field.SetCell(5, 5, CellType::LAND);

    shared_ptr<IPlayer> minimaxPlayer(new MiniMaxPlayer(CellType::WATER, 3));
    shared_ptr<IPlayer> greedy2Player(new GreedyPlayer2(CellType::LAND));

    //RunInteractiveGame(field, CellType::LAND, minimaxPlayer);

    GetStatistic(1, field, greedy2Player, minimaxPlayer, CellType::WATER, true, true);
}

double DifferenceScoreFunction(const GameField& field, CellType playerType)
{
    CellType opponentType = playerType == CellType::WATER ? CellType::LAND : CellType::WATER;
    
    return field.GetCellTypeCount(playerType) - field.GetCellTypeCount(opponentType);
}

int main()
{
    std::cout << "Hello World!\n";

    GameField field(6, 6);
    field.SetCell(0, 0, CellType::WATER);
    field.SetCell(5, 5, CellType::LAND);
    field.SetCell(0, 1, CellType::CAVITY | CellType::ICE);
    field.SetCell(0, 4, CellType::CAVITY | CellType::ICE);
    field.SetCell(3, 2, CellType::CAVITY | CellType::ICE);
    field.SetCell(5, 4, CellType::ROCK | CellType::ICE);
    field.SetCell(5, 1, CellType::ROCK | CellType::ICE);
    field.SetCell(2, 3, CellType::ROCK | CellType::ICE);

    shared_ptr<IPlayer> greedyPlayerWater(new GreedyPlayer(CellType::WATER));
    shared_ptr<IPlayer> greedy2PlayerLand(new GreedyPlayer2(CellType::LAND));
    shared_ptr<IPlayer> greedy2PlayerWater(new GreedyPlayer2(CellType::WATER));
    shared_ptr<IPlayer> minimaxPlayerWater(new MiniMaxPlayer(CellType::WATER, 4));
    shared_ptr<IPlayer> minimaxPlayerLand(new MiniMaxPlayer(CellType::LAND, 2));
    shared_ptr<IPlayer> mctsPlayerLand(new MCTSPlayer(CellType::LAND, std::chrono::duration<int>(15)));
    shared_ptr<IPlayer> interactivePlayerWater(new InteractivePlayer(CellType::WATER));
    shared_ptr<IPlayer> greedy2DifferPlayerWater(new GreedyPlayer2(CellType::WATER, DifferenceScoreFunction));

    //RunInteractiveGame(field, CellType::LAND, interactivePlayer);
    
    GetStatistic(1, field, mctsPlayerLand, greedy2PlayerWater, CellType::WATER, true, true);
//    GetStatisticAsync(5, field, mctsPlayerLand, greedy2PlayerWater, CellType::WATER, true, false);
    //test();
    //DebugMiniMax();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
