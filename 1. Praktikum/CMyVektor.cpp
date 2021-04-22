#include "CMyVektor.h"

//Calling the constructor
CMyVektor::CMyVektor() 
{};


//getting the lenght of a vector
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


//addition operator
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


//multiplication operator
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


//function(s) we need to calculate with
double func(CMyVektor x)
{
	//sin(xy) + sin(x) + cos(y);
	//- (2x1 ^ 2 - 2x1x2 + x2 ^ 2 + x3 ^ 2 - 2x1 - 4x3);
	//implementing Exponent pow(Base, Exponent) || (x.get_v)(x) -> from which position we want to have the value


	double value;

	//value = sin(x.get_v(1)) * (x.get_v(2)) + sin(x.get_v(1)) + cos(x.get_v(2)); //f function
	value = -(pow(2 * (x.get_v(0)), 2) - 2 * (x.get_v(0)) * (x.get_v(1)) + pow((x.get_v(1)), 2) + pow((x.get_v(2)), 2) - 2 * (x.get_v(0)) - 4 * (x.get_v(2))); //g function
	std::cout << "Funktionswert: " << value << std::endl;
	return value;
};


//getting the gradient
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
	std::cout << "Gradient: " << value.get_v(0) << " " << value.get_v(1) << " " << value.get_v(2) << std::endl;
	return value;
}


CMyVektor gradientenverfahren(CMyVektor x, double (*funktion)(CMyVektor x), double lambda)
{
	int step = 1;
	CMyVektor grad_xn;
	CMyVektor xnew = x; //xnew will change every loop but still needs the first starting point that was given in main
	CMyVektor xtest;
	double lambdatest = lambda;
	CMyVektor xprevtea;
	
	do
	{
		step++;

		std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) << " )" << std::endl; //function f
		//std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) <<  << " ; " << xnew.get_v(2) )" << std::endl; //function g

		std::cout << "lambda = " << lambda << std::endl;

		std::cout << "f(x) = " << func(xnew) << std::endl;

		std::cout << "grad f(x) = " << func(xnew) << std::endl;

		std::cout << "||grad f(x)|| = " << laenge(func(xnew)) << std::endl << std::endl; //Lenght from gradient

		grad_xn = gradient(xneu, func);
		xtest = lambda * grad_xn;
		xtest = xtest + xnew; //x1 = x0 + lambda * grad f(xo)
		std::cout << "x_neu = ( " << xtest.get_v(0) << " ;  " << xtest.get_v(1) << " )" << std::endl;   //Value after a step f function
		//std::cout << "x_neu = ( " << xtest.get_v(0) << " ;  " << xtest.get_v(1) <<  xtest.get_v(2) << " )" << std::endl;  //Value after a step g function

		std::cout << "f(x_neu)" << func(xtest) << std::endl << std::endl;


		//Doppelte Schrittweite
		if (func(xtest) > func(xnew))
		{
			std::cout << "Test mit doppelter Schrittweite (lambda = " << 2 * lambdatest << " ) : " << stdl::endl;

			xprevtea = xtest; 
			xtest = lambdatest * grad_xn(xnew, func);
			xtest = xtest + xnew; //x1 = x0 + lambda * grad f(xo)
			std::cout << "x_test = ( " << xtest.get_v(0) << " ; " << xtest.get_v(1) << " )" << std::endl;  //Value f function
			//std::cout << "x_test = ( " << xtest.get_v(0) << " ; " << xtest.get_v(1) << xtest.get_v(2) << " )" << std::endl; //Value g function
			std::cout << "f(x_test) = " << func(xtest) << std::endl;

			if (func(xprevtea) > func(xtest)) //
			{
				std::cout << "behalte alte Schrittweite!" << std::endl << std::endl;

				xnew = xprevtea;
				grad_xn = gradient(xnew, func);
			}

			else if (func(xprevtea) < func(xtest)) //Übergibt neue Werte zum weiterrechnen
			{
				std::cout << "verdoppele Schrittweite!" << std::endl << std::endl;

				lambda = lambdatest;
				xnew = xtest;
				grad_xn = gradient(xnew, func);
			}
			
		}


		//Halbiere Schrittweite
		else if (func(xtest) <= func(xnew))
		{
			do
			{
				lambda = lambda / 2;
				
				std::cout << "halbiere Schrittweite (lambda = " << lambda << " ) : " << stdl::endl;

				xtest = lambda * grad_xn(xnew, func);
				xtest = xtest + xnew;
				xprevtea = xtest;
				std::cout << "x_neu = ( " << xtest.get_v(0) << " ; " << xtest.get_v(1) << " )" << std::endl;  //Value f function
				//std::cout << "x_neu = ( " << xprevtea.get_v(0) << " ; " << xprevtea.get_v(1) << xprevtea.get_v(2) << " )" << std::endl; //Value g function
				std::cout << "f(x_neu) = " << func(xtest) << std::endl;

			} while (func(xtest) < func(xnew))

			xnew = xtest;
			grad_xn = gradient(xnew, func);
		}
		
		if (grad_xn.laenge(grad_xn) < pow(10, -5))
		{
			std::cout << "Ende wegen ||grad f(x)||<1e-5 bei " << std::endl;
			std::cout << "x = " << x << std::endl;
			std::cout << "lambda = " << lambda << std::endl;
			std::cout << "f(x) = " << func(xnew) << std::endl;
			std::cout << "grad f(x) = " << func(xnew) << std::endl;
			std::cout << "||grad f(x)|| = " << laenge(func(xnew)) << std::endl;
		}

		else
		{
			std::cout << "Ende wegen Schrittzahl = 25 bei " << std::endl;
			std::cout << "x = " << x << std::endl;
			std::cout << "lambda = " << lambda << std::endl;
			std::cout << "f(x) = " << func(xnew) << std::endl;
			std::cout << "grad f(x) = " << func(xnew) << std::endl;
			std::cout << "||grad f(x)|| = " << laenge(func(xnew)) << std::endl;
		}
		


	}while(step != 25 && grad_xn.laenge(grad_xn) > pow(10, -5))

}
