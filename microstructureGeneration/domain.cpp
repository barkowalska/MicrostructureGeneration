#include "domain.h"

Domain::Domain(int  x, int y)
{
	dimX = x;
	dimY = y;
	matrix = new int[x * y];
	for (int k=0; k<x*y; k++)
	{
		matrix[k] = 0;
	}

}

Domain::~Domain()
{
	//delete[] matrix;
	//delete[] neighbourhood;
}

void Domain::vonNeumann()
{
	neighbourhood = new int[8];
	neighbourhoodSize = 8;

	neighbourhood[0] = -1;
	neighbourhood[1] = 0;
	neighbourhood[2] = 1;
	neighbourhood[3] = 0; 
	neighbourhood[4] = 0;
	neighbourhood[5] = -1;
	neighbourhood[6] = 0;
	neighbourhood[7] = 1;
}

void Domain::moore()
{
	neighbourhood = new int[16];
	neighbourhoodSize = 16;

	neighbourhood[0] = -1;
	neighbourhood[1] = 0;
	neighbourhood[2] = 1;
	neighbourhood[3] = 0;
	neighbourhood[4] = 0;
	neighbourhood[5] = -1;
	neighbourhood[6] = 0;
	neighbourhood[7] = 1;

	neighbourhood[8] = -1;
	neighbourhood[9] = -1;
	neighbourhood[10] = 1;
	neighbourhood[11] = 1;
	neighbourhood[12] = -1;
	neighbourhood[13] = 1;
	neighbourhood[14] = 1;
	neighbourhood[15] = -1;
}



void Domain::nucleation()
{
	int n= grainNumber;
	
	while (n != 0)
	{
		int x = std::rand() % dimX;
		int y = std::rand() % dimY;

		matrix[y * dimX + x] = n;
		n--;
	}
}