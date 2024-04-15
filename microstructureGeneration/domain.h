#pragma once
#include <memory>

enum boundryCondition { periodic, absorbtion };

class Domain
{
private:
	int dimX;
	int dimY;
	int* matrix;
	int* neighbourhood;
	int grainNumber;
	int neighbourhoodSize;
	boundryCondition bc;

public:
	Domain(int x, int y);
	~Domain();
	int getDimX() { return dimX; }
	int getDimY() { return dimY; }
	int* getMatrix() { return matrix; }
	int* getNeighbourhood() { return neighbourhood; }
	int getGrainNumber() { return grainNumber; }
	void setGrainNumber(int grainNumberSet) { grainNumber = grainNumberSet; }
	int getNeighbourhoodSize() { return neighbourhoodSize;  }
	void setBc(boundryCondition setBc) { bc = setBc; }
	boundryCondition getBc() { return bc; }


	void vonNeumann();
	void moore();
	void nucleation();
};