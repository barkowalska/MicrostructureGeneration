#pragma once
#include "Basic_Datatypes.h"
#include <cmath>

class Neighbours
{
public:
	/*
		Zwraca pozycjê s¹siada w stosunku do komórki {x,y,z}
	*/
	virtual vec getNext() = 0;
	virtual ~Neighbours() = default;
};

/*s¹siedztwo Moore*/
class Moore:public Neighbours
{
private:
	vec pos[9];
public:
	vec getNext() override;
	Moore();
};

/*s¹siedztwo Von Neumann*/
class VonNeumann :public Neighbours
{
private:
	vec pos[5];
public:
	vec getNext() override;
	VonNeumann();
};

/*Losowe s¹siedztwo pentagonalne*/
class Random :public Neighbours
{
private:
	vec pos[9];
public:
	vec getNext() override;
	Random();
};