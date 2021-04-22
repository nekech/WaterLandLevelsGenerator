#ifndef INTERACTIVE_PLAYER
#define INTERACTIVE_PLAYER
#pragma once

#include "IPlayer.h"

class InteractivePlayer : public IPlayer
{
public:
	InteractivePlayer(CellType playerType);

	Step GetStep(const GameField& field);

	Step InputStep();
};

#endif // !INTERACTIVE_PLAYER
