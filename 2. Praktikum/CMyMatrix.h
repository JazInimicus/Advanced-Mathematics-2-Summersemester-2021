#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include "CMyVektor.h"

class CMyMatrix
{
private:
	int dimx = 0; //Rows
	int dimy = 0; //Colums
	std::vector<std::vector<double>> matrix;

public:
	CMyMatrix(); //Default Constructor 
	CMyMatrix(int x, int y); //Constructor

	int get_Dimx() { return dimx; }
	int get_Dimy() { return dimy; }

	double get_v(int x, int y) { return matrix[x][y]; }
	void set_v(int x, int y, double value) { matrix[x][y] = value; }

};

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));
CMyVektor operator*(CMyMatrix A, CMyVektor x);
CMyMatrix invers(CMyMatrix A);
