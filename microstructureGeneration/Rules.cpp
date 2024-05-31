#include "Rules.h"
class ComparePair
{
	public:
	bool operator()(const std::pair<int, int>& p)
	{
		return p.first == x;
	}
	int x;
};

int MaxNumber::value(std::vector<int>& values)
{
	std::vector<std::pair<int, int>> states;
	ComparePair cp;
	
	/*
	*	for(int i = 0; i < states.size; i++)
	*	{
			bool flag = cp(states[i]);
			if(flag == true) return ->states[i];
		}
		retrun states.end();
	*/

	for (int i = 0; i < values.size(); i++)
	{
		if (values[i] == 0) continue;
		cp.x = values[i];
		auto pair=std::find_if(states.begin(), states.end(), cp);
		if (pair == states.end()) states.push_back({ values[i], 1 });
		else
		{
			pair->second++;
		}
	}
	if (states.empty()) return 0;
	std::pair<int,int> max= states[0];
	for (std::pair<int,int> i : states)
	{
		if (max.second < i.second)max = i;
	}
	int maxValue = max.first;
	return maxValue;
}

int Energy::value(std::vector<int>& values)
{
	double Energy1 = 0;
	double Energy2 = 0;
	double E;
	int m;

	for (int i : values)
	{
		if (values.back() == i) m = 1;
		else m = 0;

		Energy1 += (1 - m);
	}

	int rand = std::rand() % 8;

	for (int i : values)
	{
		if (values[rand] == i) m = 1;
		else m = 0;

		Energy2 += (1 - m);
	}

	E = Energy2 - Energy1;

	double kt = 0.1;
	double propability;
	if (E <= 0) propability = 1;
	else
	{
		propability = exp((-1) * E / kt);
	}

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0, 1.0);

	if (propability >= dis(gen))
	{
		return values[rand];
	}
	else return values.back();
}