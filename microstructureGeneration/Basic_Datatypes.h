#pragma once
struct vector
{
	int x;
	int y;
	int z;

	vector operator+(const vector& v)
	{
		return { x + v.x,y + v.y, z + v.z };
	}

	vector& operator=(const vector& v)
	{
		x = v.x, y = v.y, z = v.z;
		return *this;
	}

	bool operator!=(const vector& v)
	{
		return 	(x != v.x) || (y != v.y) || (z != v.z);

	}

};