#ifndef VECTOR2
#define VECTOR2
#pragma once

#include <nlohmann/json.hpp>

#include <ostream>

template<typename T>
class Vector2
{
public:

	T x;
	T y;
    
    Vector2()
    {
    }

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

namespace nlohmann {
    template <typename T>
    struct adl_serializer<Vector2<T>> {
        static void to_json(json& j, const Vector2<T>& opt) {
            j["x"] = opt.x;
            j["y"] = opt.y;
        }

        static void from_json(const json& j, Vector2<T>& opt) {
            opt.x = j["x"].get<T>();
            opt.y = j["y"].get<T>();
        }
    };
}

#endif // !VECTOR2
