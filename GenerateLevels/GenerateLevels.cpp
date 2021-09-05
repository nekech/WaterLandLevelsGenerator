// GenerateLevels.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <tuple>
#include <chrono>

#include <nlohmann/json.hpp>

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

#include "Level.h"

#include "Raiting.h"

template<typename T>
using shared_ptr = std::shared_ptr<T>;

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

    RunInteractiveGame(field, CellType::LAND, minimaxPlayer);
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
    shared_ptr<IPlayer> minimaxPlayerLand(new MiniMaxPlayer(CellType::LAND, 4));
    shared_ptr<IPlayer> mctsPlayerLand(new MCTSPlayer(CellType::LAND, std::chrono::duration<int>(15)));
    shared_ptr<IPlayer> interactivePlayerWater(new InteractivePlayer(CellType::WATER));
    shared_ptr<IPlayer> greedy2DifferPlayerWater(new GreedyPlayer2(CellType::WATER, DifferenceScoreFunction));

    //RunInteractiveGame(field, CellType::LAND, interactivePlayer);
    
    //***************************************************************************************
    //**********************COMPUTE RAITING**************************************************
    
    
    shared_ptr<IPlayer> minimaxPlayerWater2(new MiniMaxPlayer(CellType::WATER, 2));
    shared_ptr<IPlayer> minimaxPlayerWater3(new MiniMaxPlayer(CellType::WATER, 3));
    shared_ptr<IPlayer> minimaxPlayerWater4(new MiniMaxPlayer(CellType::WATER, 4));
    
    Raiting raitingT1(field, 10);
    
    raitingT1.AddPlayer(greedyPlayerWater);
    raitingT1.AddPlayer(greedy2PlayerWater);
    raitingT1.AddPlayer(minimaxPlayerWater2);
    raitingT1.AddPlayer(minimaxPlayerWater3);
    raitingT1.AddPlayer(minimaxPlayerWater4);
    
    raitingT1.ComputeRaiting();
    
    raitingT1.PrintRaiting();
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
