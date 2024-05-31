#include "Simulation.h"
Simulation::Simulation(int x, int y, int z):domain_(x,y,z){}

void Simulation::run()
{
	Domain domain_cpy(domain_);
	Domain* output = &domain_cpy;
	for (int i = 0; i < iterations; i++) 
	{
		for (int z = 0; z < domain_.getDimZ(); z++)
			for (int y = 0; y < domain_.getDimY(); y++)
				for (int x = 0; x < domain_.getDimX(); x++)
				{
					std::vector<int> values;
					vec temp;
					do
					{
						temp = neighbours_->getNext();
						if ((temp.x + x) < 0 || (temp.x + x) >= domain_.getDimX() || (temp.y + y) < 0 || (temp.y + y) >= domain_.getDimY() || (temp.z + z) < 0 || (temp.z + z) >= domain_.getDimZ())
						{
							int k = value(temp.x + x, temp.y + y, temp.z + z);
							values.push_back(k);

						}
						else values.push_back((*input)(temp.x + x, temp.y + y, temp.z + z));

					} while (temp != vec{ 0,0,0 });
					(*output)(x, y, z) = rule_->value(values);
				}
		std::swap(input, output);
	}
	if (iterations % 2 == 1) domain_ = domain_cpy;
}

int Simulation::value(int x, int y, int z)
{
	int value=0;
	
	switch (domain_.getBc()) {
	case periodic:
	{
		int nX = 0;
		int nY = 0;
		int nZ = 0;
		if (x < 0)
		{
			x = domain_.getDimX() - 1;
		}
		else if (x >= domain_.getDimX())
		{
			x = 0;
		}
		if (y < 0)
		{
			y = domain_.getDimY() - 1;
		}
		else if (y >= domain_.getDimY())
		{
			y = 0;
		}
		if (z < 0)
		{
			z = domain_.getDimZ() - 1;
		}
		else if (z >= domain_.getDimZ())
		{
			z = 0;
		}
		value = (*input)(x, y, z);
	}
		break;
	case absorbtion:
		break;
	}
	return value;
}

//przechodzi po wszystkich komorkach losuje jedna bez zwracania, przekazuje do funkcji liczacej energie jednej komorki
void Simulation::randomCel()
{
	std::vector<vec> randomOrder;
	randomOrder.reserve(domain_.getDimX() * domain_.getDimY() * domain_.getDimZ());

	for (int z = 0; z < domain_.getDimZ(); z++)
		for (int y = 0; y < domain_.getDimY(); y++)
			for (int x = 0; x < domain_.getDimX(); x++)
			{
				randomOrder.emplace_back(x, y, z);
			}

	std::random_shuffle(randomOrder.begin(), randomOrder.end());

for(vec &v: randomOrder)
	{
		energy(v.x, v.y, v.z);		
	}

}

//bierze komorke, przechodzi sasiadow, oblicza energie, zwraca energie i liste wartiosci sasiadow
void Simulation::energy(int x, int y, int z)
{
	std::vector<int> values;
	
	int k;
	int m = 0;
	vec temp;
	do
	{
		temp = neighbours_->getNext();
		if ((temp.x + x) < 0 || (temp.x + x) >= domain_.getDimX() || (temp.y + y) < 0 || (temp.y + y) >= domain_.getDimY() || (temp.z + z) < 0 || (temp.z + z) >= domain_.getDimZ())
		{
			k = value(temp.x + x, temp.y + y, temp.z + z);

		}
		else k=domain_(temp.x + x, temp.y + y, temp.z + z);

		values.push_back(k);

	} while (temp != vec{ 0,0,0 });
	
	domain_(x,y,z)=  rule_->value(values);

}


