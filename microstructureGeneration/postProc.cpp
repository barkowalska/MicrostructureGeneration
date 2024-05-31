#include "domain.h"
#include "EasyBMP.h"
#include <cstdlib>
#include<iostream>
#include "postProc.h"
#include <vector>
#include <algorithm>

void picture(Domain& domain, std::string name )
{
	srand(time(NULL));
	int grainNum = domain.getGrainNumber();
	int* colorArray = new int[3 * grainNum];
	for (int i = 0; i < grainNum; i++)
	{
		colorArray[i * 3] = std::rand() % 256;
		colorArray[(i * 3) + 1] = std::rand() % 256;
		colorArray[(i * 3) + 2] = std::rand() % 256;
	}

	BMP bmp;
	bmp.SetSize(domain.getDimX(), domain.getDimY());
	for (int y = 0; y < domain.getDimY(); y++)
	{
		for (int x = 0; x < domain.getDimX(); x++)
		{
			RGBApixel pixel;
			int value = domain(x, y, 0);
			if (value == 0)
			{
				pixel.Red = 0;
				pixel.Blue = 0;
				pixel.Green = 0;
			}
			else
			{
				pixel.Red = colorArray[value * 3];
				pixel.Green = colorArray[value * 3 + 1];
				pixel.Blue = colorArray[value * 3 + 2];

			}
			bmp.SetPixel(x, y, pixel);
		}
	}

	bmp.WriteToFile(name.c_str());
}
	

