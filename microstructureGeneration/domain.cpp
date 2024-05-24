#include "domain.h"

Domain::Domain(int  x, int y, int z)
{
	dimX = x;
	dimY = y;
	dimZ = z;
	matrix = std::shared_ptr<int[]>(new int[x*y*z]);
	for (int k=0; k<x*y*z; k++)
	{
		matrix[k] = 0;
	}

}

/*Konstruktor kopiuj¹cy*/
Domain::Domain(const Domain& domain)
{
	dimX = domain.dimX;
	dimY = domain.dimY;
	dimZ = domain.dimZ;
	matrix = std::shared_ptr<int[]>(new int[dimX * dimY * dimZ]);
	for (int k = 0; k < dimX * dimY * dimZ; k++)
	{
		matrix[k] = domain.matrix[k];
	}
}

Domain& Domain::operator=(const Domain& domain)
{
	dimX = domain.dimX;
	dimY = domain.dimY;
	dimZ = domain.dimZ;
	matrix.reset();
	matrix = std::shared_ptr<int[]>(new int[dimX * dimY * dimZ]);
	for (int k = 0; k < dimX * dimY * dimZ; k++)
	{
		matrix[k] = domain.matrix[k];
	}
	return *this;
}

Domain::~Domain() {	}

/*Zarodkowanie losowe*/
void Domain::nucleation_random()
{
	int n= grainNumber;
	
	while (n != 0)
	{
		int x = std::rand() % dimX;
		int y = std::rand() % dimY;
		int z = std::rand() % dimZ;

		matrix[z* dimX* dimY + y * dimX + x] = n;
		n--;
	}
}
/*zarodkowanie jednorodne*/
void Domain::nucleation_uniform()
{
	int n = grainNumber;
	int kloc = (dimY* dimX) / n;
	int pier = sqrt(kloc);
	int x = pier/2;
	int y = pier/2;

	while (x < dimX && n>0)
	{

		while (y < dimY)
		{
			matrix[y * dimX + x] = n;
			y += pier;
			n--;
		}
		y = pier / 2;
		x += pier;
	}
}