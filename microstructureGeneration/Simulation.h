#pragma once
#include "Rules.h"
#include "Neighbours.h"
#include <memory>
#include "domain.h"

class Simulation
{
private:
	std::shared_ptr<Rules> rule_;
	std::shared_ptr<Neighbours> neighbours_;
	Domain domain_;
	Domain* input{ &domain_ };
	int iterations;
public:
	Simulation(int x, int y, int z);
	void setIterations(int i) { iterations = i; }
	int getIterations() { return iterations; }
	void rule(std::shared_ptr<Rules> rule) { this->rule_ = rule; }
	void neighbour(std::shared_ptr<Neighbours> neighbour) { this->neighbours_ = neighbour; }
	Domain& domain() { return domain_; }
	void run();
	int value(int x, int y, int z);
};

