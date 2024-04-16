#include "domain.h"



template<typename T>
void swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

int* allocateMatrix(Domain& domain);
void setConstantCache(Domain& domain);
void run(int* matrixInput, int* matrixOutput, Domain& domain, int iteracions);