#include "postProc.h"
#include "domain.h"
#include "kernels.cuh"
#include <iostream>
#include "cuda_runtime.h"
#include "Simulation.h"
#include"Neighbours.h"
#include <vector>
#include <unordered_set>

void allDelete(Domain& domain);
void IDDelete(Domain& domain, std::unordered_set<int> &toRemove);


int main()
{
	int x = 100;
	int y = 100;
	int z = 1;
	std::cout << "Please enter x dimension "<< std::endl;
	std::cin >> x;
	std::cout << "Please enter y dimension " << std::endl;
	std::cin >> y;
	std::cout << "Please enter z dimension " << std::endl;
	std::cin >> z;

	Simulation sim(x, y, z);
	int grainNumber =9;
	
	std::cout << "Please enter Grain number " << std::endl;
	std::cin >> grainNumber;

	sim.domain().setGrainNumber(grainNumber);

	boundryCondition setBc;
	sim.domain().setBc(boundryCondition::absorbtion);
	std::cout << "Please enter baundry condition: 1 for periodic, 2 for absorbtion " << std::endl;
	std::cin >> x;
	if(x == 2) setBc = boundryCondition::absorbtion;
	if(x == 1) setBc = boundryCondition::periodic;

	sim.domain().setBc(setBc);
	sim.domain().nucleation_uniform();
	sim.neighbour(std::shared_ptr<Neighbours>(new Random));
	sim.rule(std::shared_ptr<Rules>(new MaxNumber));

	int iteracions =10;

	std::cout << "Please enter number of iteracions" << std::endl;
	std::cin >> iteracions;
	sim.setIterations(iteracions);
	sim.run();
	
	std::unordered_set<int> toRemove {1,6,2,5};

	picture(sim.domain(), "result1.bmp");

	sim.randomCel();
	picture(sim.domain(),"result2.bmp");

	return 0;
}


void allDelete(Domain& domain)
{
	for (int z = 0; z < domain.getDimZ(); z++)
		for (int y = 0; y < domain.getDimY(); y++)
			for (int x = 0; x < domain.getDimX(); x++)
			{
				if (domain(x, y, z) != 0) domain(x, y, z) = 0;
				else if (domain(x, y, z) == 0) domain(x, y, z) = 1;
			}
}



void IDDelete(Domain& domain, std::unordered_set<int>& toRemove) 
{
	int k;
	for (int z = 0; z < domain.getDimZ(); z++)
		for (int y = 0; y < domain.getDimY(); y++)
			for (int x = 0; x < domain.getDimX(); x++)
			{
				k = domain(x, y, z);
				if (toRemove.find(k) != toRemove.end()) domain(x, y, z) = 0; 
			}
}
