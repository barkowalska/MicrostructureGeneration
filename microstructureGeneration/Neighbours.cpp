#include "Neighbours.h"

Moore::Moore()
{
	int i = 0;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (x == 0 && y == 0)pos[8] = { x,y,0 };
			else
			{
				pos[i] = { x,y, 0 };
				i++;
			}
		}
	}
}


vector Moore::getNext()
{
	static int index = -1;
	index++;
	if (index == 9) index = 0;
	return pos[index]; 
}

VonNeumann::VonNeumann()
{
	int i = 0;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (x == 0 && y == 0)pos[4] = { x,y,0 };
			else if (abs(x) == abs(y))continue;
			else
			{
				pos[i] = { x,y, 0 };
				i++;
			}
		}
	}
}

vector VonNeumann::getNext()
{
	static int index = -1;
	index++;
	if (index == 5) index = 0;
	return pos[index];
}

Random::Random()
{
	int i = 0;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (x == 0 && y == 0)pos[8] = { 0,0,0 };
			else
			{
				pos[i] = { x,y, 0 };
				i++;
			}
		}
	}
	
}

vector Random::getNext()
{
	static int i = std::abs(rand()%7);
	i++;
	static int index = -1;
	index++;
	if (index == 5)
	{
		i = std::abs(rand() % 7);
		index = 0;
		return pos[8];
	}
	else if (i > 7)i = 0;
	return pos[i];
}