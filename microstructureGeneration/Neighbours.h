#pragma once
#include "Basic_Datatypes.h"
#include <cmath>

class Neighbours
{
public:
	/*
		Zwraca pozycj� s�siada w stosunku do kom�rki {x,y,z}
	*/
	virtual vector getNext() = 0;
	virtual ~Neighbours() = default;
};

class Moore:public Neighbours
{
private:
	vector pos[9];
public:
	vector getNext() override;
	Moore();
};

class VonNeumann :public Neighbours
{
private:
	vector pos[5];
public:
	vector getNext() override;
	VonNeumann();
};

class Random :public Neighbours
{
private:
	vector pos[9];
public:
	vector getNext() override;
	Random();
};