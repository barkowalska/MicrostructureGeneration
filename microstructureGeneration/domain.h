#pragma once
#include <memory>
#include <vector>
#include"Basic_Datatypes.h"

enum boundryCondition { periodic, absorbtion };

class Domain
{
private:
	int dimX;
	int dimY;
	int dimZ;
	std::shared_ptr<int[]> matrix;
	int grainNumber;
	boundryCondition bc;

public:
	Domain(int x, int y, int z);
	Domain(const Domain& domain);
	Domain& operator=(const Domain&);
	~Domain();
	int getDimX() const { return dimX; }
	int getDimY() const { return dimY; }
	int getDimZ() const { return dimZ; }
	int* getMatrix() { return matrix.get(); }
	int getGrainNumber() { return grainNumber; }
	void setGrainNumber(int grainNumberSet) { grainNumber = grainNumberSet; }
	void setBc(boundryCondition setBc) { bc = setBc; }
	boundryCondition getBc() { return bc; }
	/*Zwraca referencje do komorki*/
	int& operator()(int x, int y, int z) { 
		return matrix.get()[z * dimX * dimY + y * dimX + x]; 
	}

	void nucleation_random();
	void nucleation_uniform();

};

