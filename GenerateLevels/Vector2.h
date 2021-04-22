#ifndef VECTOR2
#define VECTOR2
#pragma once

#include <ostream>

template<typename T>
class Vector2
{
public:

	T x;
	T y;

	Vector2(T x, T y):x(x), y(y)
	{
	}

	Vector2(T v): x(v), y(v)
	{
	}

	bool operator==(const Vector2<T> other)
	{
		return x == other.x && y == other.y;
	}

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const Vector2<U> vector);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T> vector)
{
	os << "( "<<vector.x<<" , "<<vector.y<<" )";
	return os;
}

#endif // !VECTOR2