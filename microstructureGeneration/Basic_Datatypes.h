#pragma once
#include <unordered_set>
struct vec
{
	int x;
	int y;
	int z;
	
	// Konstruktor domyœlny
	vec() : x(0), y(0), z(0) {}

	// Konstruktor z parametrami
	vec(int a, int b, int c) : x(a), y(b), z(c) {}

	// Konstruktor kopiuj¹cy
	vec(const vec& v) : x(v.x), y(v.y), z(v.z) {}

	
	vec operator+(const vec& v)
	{
		return { x + v.x,y + v.y, z + v.z };
	}

	vec& operator=(const vec& v)
	{
		x = v.x, y = v.y, z = v.z;
		return *this;
	}

	bool operator!=(const vec& v)
	{
		return 	(x != v.x) || (y != v.y) || (z != v.z);

	}

	// Operator równoœci (wymagany przez std::unordered_set)
	bool operator==(const vec& v) const {
		return (x == v.x) && (y == v.y) && (z == v.z);
	}

	// Specjalizacja szablonu std::hash dla struktury vector

	

};

namespace std {
	template <>
	struct hash<vec> {
		std::size_t operator()(const vec& v) const noexcept {
			return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) ^ std::hash<int>()(v.z);
		}
	};
}
