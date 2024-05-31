#pragma once
#include <chrono>

class Stats
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> stop;

public:
	void startTime();
	void stopTime();
	
};