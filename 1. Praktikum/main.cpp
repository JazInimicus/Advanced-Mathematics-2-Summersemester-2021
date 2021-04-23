#include <iostream>
#include <math.h>
#include <vector>
#include "CMyVektor.h"

int main()
{
	
	//Tests during debugging
	/*
	CMyVektor vektor = CMyVektor();
	vektor.set_d(3);
	vektor.set_v(0, 0); vektor.set_v(1, 0); vektor.set_v(2, 0);
	vektor.laenge(vektor);

	func(vektor);

	gradient(vektor, func); */


	//for Function f
	CMyVektor vector = CMyVektor();
	vector.set_d(2);
	vector.set_v(0, 0.2);
	vector.set_v(1, -2.1);

	gradientenverfahren(vector, func, 1);


	//for Function g
	/*
	CMyVektor vector = CMyVektor();
	vector.set_d(3);
	vector.set_v(0, 0);
	vector.set_v(1, 0);
	vector.set_v(2, 0);

	gradientenverfahren(vector, func, 0.1); */

	system("PAUSE");
	return 0;
}