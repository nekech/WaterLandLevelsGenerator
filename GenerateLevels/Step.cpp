#include "Step.h"

Step::Step(Vector2<int> from, Vector2<int> to) :from(from), to(to)
{
}

Step::Step(Vector2<int> from, Vector2<int> to, bool isLong) :from(from), to(to), isLong(isLong)
{
}

Step::Step() :from(Vector2<int>(-1)), to(Vector2<int>(-1))
{
}
