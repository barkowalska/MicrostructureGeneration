#include "kernels.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<iostream>

__constant__ int bc;
__constant__ int neighbourhood[32];
__constant__ int dimY;
__constant__ int dimX;
__constant__ int NeighbourhoodSize;

int* allocateMatrix(Domain& domain)
{
	int* matrixD;
	cudaMalloc(&matrixD, sizeof(int) * domain.getDimX() * domain.getDimY());
	cudaMemcpy(matrixD, domain.getMatrix(), sizeof(int) * domain.getDimY() * domain.getDimX(), cudaMemcpyHostToDevice);
	return matrixD;
}

void setConstantCache(Domain& domain)
{
	int dDimY = domain.getDimY();
	int dDimX = domain.getDimX();
	int nSize = domain.getNeighbourhoodSize();
	int BC = domain.getBc();

	cudaMemcpyToSymbol(dimY, &dDimY, sizeof(int));
	cudaMemcpyToSymbol(dimX, &dDimX, sizeof(int));
	cudaMemcpyToSymbol(NeighbourhoodSize, &nSize, sizeof(int));
	cudaMemcpyToSymbol(neighbourhood, domain.getNeighbourhood(), sizeof(int) * nSize);
	cudaMemcpyToSymbol(bc, &BC, sizeof(int));
	
}

void __global__ growGrain(int* matrixInput, int* matrixOutput)
{
	__shared__ int local_matrix[32][32];
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	if (x  >= dimX || y >= dimY) return;

	local_matrix[threadIdx.y][threadIdx.x] = matrixInput[y * dimX + x];
	for (int k = 0; k < NeighbourhoodSize; k+=2)
	{	
		if ((x + neighbourhood[k]) >= dimX || (y + neighbourhood[k + 1]) >= dimY || (x + neighbourhood[k]) < 0 || (y + neighbourhood[k + 1]) < 0)
		{
			switch (bc) {
			case periodic:
			{
				int nX;
				int nY;
				if ((x + neighbourhood[k]) >= dimX)
				{
					nX = 0;
				}
				if ((y + neighbourhood[k + 1]) >= dimY)
				{
					nY = 0;
				}
				if ((x + neighbourhood[k]) < 0)
				{
					nX = dimX - 1;
				}
				if ((y + neighbourhood[k + 1]) < 0)
				{
					nY = dimY - 1;
				}
				local_matrix[threadIdx.y][threadIdx.x] = local_matrix[threadIdx.y][threadIdx.x] + matrixInput[dimX * nY + nX] * (local_matrix[threadIdx.y][threadIdx.x] == 0);
				break;
			}
			case absorbtion:
				
				break;
			}

		}
		else local_matrix[threadIdx.y][threadIdx.x] = 
			local_matrix[threadIdx.y][threadIdx.x] + (local_matrix[threadIdx.y][threadIdx.x] == 0) * matrixInput[x + neighbourhood[k] + (y + neighbourhood[k + 1]) * dimX];
	}
	matrixOutput[y * dimX + x] = local_matrix[threadIdx.y][threadIdx.x];


}



void run(int* matrixInput, int* matrixOutput, Domain &domain, int iteracions)
{
	dim3 blockSize = { 32, 32, 1 };
	dim3 gridSize = { (domain.getDimX() + blockSize.x - 1) / blockSize.x, (domain.getDimY() + blockSize.y - 1) / blockSize.y, 1 };
	std::cout << gridSize.x << ' ' << gridSize.y << ' ' << gridSize.z << std::endl;
	for (int i = 0; i < iteracions; i++)
	{
		growGrain<<<gridSize, blockSize>>>(matrixInput, matrixOutput);
		cudaDeviceSynchronize();
		
		int* tmp = matrixInput;
		matrixInput = matrixOutput;
		matrixOutput = tmp;
	}

	cudaMemcpy(domain.getMatrix(),matrixInput , sizeof(int) * domain.getDimY() * domain.getDimX(), cudaMemcpyDeviceToHost);

	cudaFree(matrixInput);
	cudaFree(matrixOutput);
}