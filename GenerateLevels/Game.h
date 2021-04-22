#ifndef GAME
#define GAME
#pragma once

#include <memory>

#include "GameField.h"
#include "IPlayer.h"

template<class T>
using shared_ptr = std::shared_ptr<T>;

class Game
{
public:
	GameField field;

	CellType currentPlayer;

	shared_ptr<IPlayer> playerOne; //TODO make uniqueptr
	shared_ptr<IPlayer> playerTwo;

	Game(const GameField& field, CellType startPlayer, shared_ptr<IPlayer> playerOne, shared_ptr<IPlayer> playerTwo);

	void Start(bool debug = false);

	void ChangePlayer();

	CellType GetWinner();
};

#endif // !GAME
