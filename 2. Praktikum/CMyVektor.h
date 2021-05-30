#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include "CMyMatrix.h"

class CMyVektor
{
private:
	int dimension = 0;
	std::vector<double> vektor; //because fuck Arrays

public:
	CMyVektor(); //Constructor
	CMyVektor(int x);

	int get_d() { return dimension; }
	//void set_d(int x) { dimension = x; vektor.resize(dimension, 0); }

	double get_v(int y) { return vektor[y]; } //returns value of the private vektor attribute
	void set_v(int x, double s) { vektor[x] = s; } //at point x, set the value s to the vektor attribute

	double laenge(CMyVektor vektor);
};


CMyVektor operator+(CMyVektor a, CMyVektor b);
CMyVektor operator*(double lambda, CMyVektor a);
CMyVektor func(CMyVektor x);
CMyVektor func2(CMyVektor x);
void newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));

/*
CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x));
CMyVektor gradientenverfahren(CMyVektor x, double (*funktion)(CMyVektor x), double lambda);
*/
