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