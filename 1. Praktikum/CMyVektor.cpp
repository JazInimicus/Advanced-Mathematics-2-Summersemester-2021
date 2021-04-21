#include "CMyVektor.h"

CMyVektor::CMyVektor() //Calling the constructor
{};

double CMyVektor::laenge(CMyVektor vektor) //sqrt(x1^2+....+xn^2)
{
	double laenge = 0;

	for (int i = 0; i < vektor.get_d(); i++)
	{ 
		laenge = laenge + (vektor.get_v(i) * vektor.get_v(i)); //takes value from loop before and just adds the value new until the end of the loop
	}
	laenge = sqrt(laenge); //since it's in a squareroot, need to get the value from that

	std::cout << laenge << std::endl;
	return laenge;
}

double func(CMyVektor x)
{
	double value;
	
	//sin(xy) + sin(x) + cos(y);
	//- (2x1 ^ 2 - 2x1x2 + x2 ^ 2 + x3 ^ 2 - 2x1 - 4x3);
	//implementing Exponent pow(Base, Exponent) || (x.get_v)(x) -> from which position we want to have the value


	//value = sin(x.get_v(1)) * (x.get_v(2)) + sin(x.get_v(1)) + cos(x.get_v(2));
	value = -(pow(2 * (x.get_v(0)), 2) - 2 * (x.get_v(0)) * (x.get_v(1)) + pow((x.get_v(1)), 2) + pow((x.get_v(2)), 2) - 2 * (x.get_v(0)) - 4 * (x.get_v(2)));
	std::cout << "Funktionswert: "<< value << std::endl;
	return value;
};

CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x)) //g = ((f(xi+h), xn) - f(xn)/h) || f(x0,y0,z0) = (f(x0+h, y0, z0) - f(x0,y0,z0))/h -> +h jeweils noch für die Funktion die man gerade ableitet
{
	const double h = pow(10, -8);

	CMyVektor value;

	value.set_d(x.get_d());
	
	for (int i = 0; i < x.get_d(); i++)
	{
		double v = x.get_v(i); //saves x1 value to v
		
		x.set_v(i, x.get_v(i) + h); //to value needs to be added the +h so that the right value will be put into the function
		value.set_v(i, funktion(x)); //saves value at point i, and calls function with starting point x

		x.set_v(i, v); //sets value back to starting point for new loop

		value.set_v(i, (value.get_v(i) - funktion(x)) / h); //calculates the "whole" value at point i 
	}
	std::cout << "Gradient: " << value.get_v(0)<< " " << value.get_v(1) << " " << value.get_v(2) << std::endl;
	return value;
} 

CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	CMyVektor addition;

	addition.set_d(a.get_d()); //vector of the endresult only needs to be as big as one of the vectors

	if (a.get_d() == b.get_d()) //a and b need to have the same dimension or else they couldn't be added
	{
		for (int i = 0; i <= a.get_d() && i <= b.get_d(); i++) //aomething like .size -> i can only get as big as the dimension of the two vectors
		{
			double ab = a.get_v(i) + b.get_v(i);
			addition.set_v(i, ab);
		}

		return addition;
	}
	else
	{
		std::cout << "a und b haben nicht die gleiche Dimension!";
	}
}

CMyVektor operator*(double lambda, CMyVektor a)
{
	CMyVektor multiplikation;

	multiplikation.set_d(a.get_d());

	for (int i = 0; i <= a.get_d(); i++)
	{
		double la = lambda * a.get_v(i);
		multiplikation.set_v(i, la);
	}

	return multiplikation;
}
