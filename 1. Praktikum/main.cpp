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
	CMyVektor x;

	x.set_v(0, 0.2);
	x.set_v(1, -2.1);

	gradientenverfahren(x, func, 1);


	//for Function g

	CMyVektor x;

	x.set_v(0, 0);
	x.set_v(1, 0);
	x.set_v(2, 0);

	gradientenverfahren(x, func, 0.1);

	system("PAUSE");
	return 0;
}