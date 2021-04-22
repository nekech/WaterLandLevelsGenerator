#ifndef STEP
#define STEP
#pragma once

#include "Vector2.h"

class Step
{
public:

	Vector2<int> from;
	Vector2<int> to;

	bool isLong = false;

	Step(Vector2<int> from, Vector2<int> to);

	Step(Vector2<int> from, Vector2<int> to, bool isLong);

	Step();
};

#endif // !STEP