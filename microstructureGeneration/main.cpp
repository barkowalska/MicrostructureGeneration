#include "postProc.h"
#include "domain.h"
#include "kernels.cuh"
#include <iostream>
#include "cuda_runtime.h"
#include "Simulation.h"
#include"Neighbours.h"

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
	int grainNumber =0;
	
	std::cout << "Please enter Grain number " << std::endl;
	std::cin >> grainNumber;

	sim.domain().setGrainNumber(grainNumber);

	boundryCondition setBc;

	std::cout << "Please enter baundry condition: 1 for periodic, 2 for absorbtion " << std::endl;
	std::cin >> x;
	if(x == 2) setBc = boundryCondition::absorbtion;
	if(x == 1) setBc = boundryCondition::periodic;

	sim.domain().setBc(setBc);
	sim.domain().setBc(boundryCondition::absorbtion);
	sim.domain().nucleation_uniform();
	sim.neighbour(std::shared_ptr<Neighbours>(new Random));
	sim.rule(std::shared_ptr<Rules>(new MaxNumber));

	int iteracions =0;

	std::cout << "Please enter number of iteracions" << std::endl;
	std::cin >> iteracions;
	sim.setIterations(iteracions);
	sim.run();
	picture(sim.domain());
	return 0;
}