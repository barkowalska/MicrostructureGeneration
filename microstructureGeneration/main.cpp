#include "postProc.h"
#include "domain.h"
#include "kernels.cuh"
#include <iostream>
#include "cuda_runtime.h"

int main()
{
	int x;
	int y;
	std::cout << "Please enter x dimension "<< std::endl;
	std::cin >> x;
	std::cout << "Please enter y dimension " << std::endl;
	std::cin >> y;

	Domain domain(x,y);
	int grainNumber;
	
	std::cout << "Please enter Grain number " << std::endl;
	std::cin >> grainNumber;

	domain.setGrainNumber(grainNumber);

	boundryCondition setBc;

	std::cout << "Please enter baundry condition: 1 for periodic, 2 for absorbtion " << std::endl;
	std::cin >> x;
	if(x == 2) setBc = boundryCondition::absorbtion;
	if(x == 1) setBc = boundryCondition::periodic;

	domain.setBc(setBc);

	domain.nucleation();
	domain.vonNeumann();

	int* matrixInput=allocateMatrix(domain);
	int* matrixOutput=allocateMatrix(domain);
	setConstantCache(domain);
	
	int iteracions;

	std::cout << "Please enter number of iteracions" << std::endl;
	std::cin >> iteracions;


	run(matrixInput, matrixOutput, domain, iteracions);

	cudaDeviceReset();
		picture(domain);
	return 0;
}