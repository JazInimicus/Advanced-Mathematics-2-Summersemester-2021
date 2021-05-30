#pragma once
#include "CMyVektor.h"

class C_DGLSolver
{
private:
	bool DGL_nterorder = false;
	CMyVektor(*f_DGL_System)(CMyVektor y, double x);
	double (*f_DGL_nterOrdnung)(CMyVektor y, double x);

	CMyVektor ableitungen(CMyVektor y, double x);


public:
	C_DGLSolver(CMyVektor(*_f_DGL_System)(CMyVektor y, double x))
	{
		DGL_nterorder = false;
		f_DGL_System = _f_DGL_System;

	}


	C_DGLSolver(double (*_f_DGL_nterOrdnung)(CMyVektor y, double x))
	{
		DGL_nterorder = true;
		f_DGL_nterOrdnung = _f_DGL_nterOrdnung;
	}



	CMyVektor euler(double start, double end, int step, CMyVektor y_Start);
	CMyVektor heun(double start, double end, int step, CMyVektor y_Start);

	CMyVektor euleroA(double start, double end, int steps, CMyVektor y_Start);
	CMyVektor heunoA(double start, double end, int step, CMyVektor y_Start);

};

