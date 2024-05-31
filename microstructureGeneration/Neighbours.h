#pragma once
#include "Basic_Datatypes.h"
#include <cmath>

class Neighbours
{
public:
	/*
		Zwraca pozycj� s�siada w stosunku do kom�rki {x,y,z}
	*/
	virtual vec getNext() = 0;
	virtual ~Neighbours() = default;
};

/*s�siedztwo Moore*/
class Moore:public Neighbours
{
private:
	vec pos[9];
public:
	vec getNext() override;
	Moore();
};

/*s�siedztwo Von Neumann*/
class VonNeumann :public Neighbours
{
private:
	vec pos[5];
public:
	vec getNext() override;
	VonNeumann();
};

/*Losowe s�siedztwo pentagonalne*/
class Random :public Neighbours
{
private:
	vec pos[9];
public:
	vec getNext() override;
	Random();
};