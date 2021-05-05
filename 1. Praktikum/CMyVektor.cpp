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

	//std::cout << laenge << std::endl;
	return laenge;
}


//addition operator
CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	CMyVektor addition;

	addition.set_d(a.get_d()); //vector of the endresult only needs to be as big as one of the vectors

	if (a.get_d() == b.get_d()) //a and b need to have the same dimension or else they couldn't be added
	{
		for (int i = 0; i < a.get_d() && i < b.get_d(); i++) //aomething like .size -> i can only get as big as the dimension of the two vectors
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

	for (int i = 0; i < a.get_d(); i++)
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

	//value = sin((x.get_v(0)) * (x.get_v(1))) + sin(x.get_v(0)) + cos(x.get_v(1)); //f function
	value = -(2 * pow((x.get_v(0)), 2) - 2 * ((x.get_v(0)) * (x.get_v(1))) + pow((x.get_v(1)), 2) + pow((x.get_v(2)), 2) - 2 * (x.get_v(0)) - 4 * (x.get_v(2))); //g function
	//std::cout << "Funktionswert: " << value << std::endl;

	//Praktikumstest
	//value = (3 * pow(x.get_v(0), 2)) + (2 * x.get_v(1) * pow(x.get_v(2), 2));
	return value;
};


//getting the gradient
CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x)) //g = ((f(xi+h), xn) - f(xn)/h) || f(x0,y0,z0) = (f(x0+h, y0, z0) - f(x0,y0,z0))/h -> +h jeweils noch für die Funktion die man gerade ableitet
{
	const double h = 1e-8; //pow(10, -8)

	//Praktikumstest
	//const double h = 0.1;

	CMyVektor value;
	double v = 0.0;
	double fx = funktion(x);

	value.set_d(x.get_d());

	for (int i = 0; i < x.get_d(); i++)
	{
		v = x.get_v(i); //saves x1 value to v

		x.set_v(i, v + h); //to value needs to be added the +h so that the right value will be put into the function
		value.set_v(i, funktion(x)); //saves value at point i, and calls function with starting point x

		x.set_v(i, v); //sets value back to starting point for new loop

		value.set_v(i, (value.get_v(i) - fx) / h); //calculates the "whole" value at point i 
	}
	//std::cout << "Gradient: " << value.get_v(0) << " " << value.get_v(1) << std::endl; //f function
	//std::cout << "Gradient: " << value.get_v(0) << " " << value.get_v(1) << " " << value.get_v(2) << std::endl; //g function
	return value;
}


CMyVektor gradientenverfahren(CMyVektor x, double (*funktion)(CMyVektor x), double lambda)
{
	int step = 0;
	CMyVektor grad_xn; //gradient xnew
	//grad_xn.set_d(2); //function f
	grad_xn.set_d(3); //function g
	CMyVektor xnew = x; //xnew will change every loop but still needs the first starting point that was given in main
	CMyVektor xtest; //test steps
	double lambdatest = lambda; //when doubling lambda
	CMyVektor xprevtea; //saving previous x test
	double limit = 1e-5;

	do
	{
		std::cout << std::endl;
		//step++; //step counter
		std::cout << "Schritt " << step << ": " << std::endl;

		//std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) << " )" << std::endl; //function f
		std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) << " ; " << xnew.get_v(2) << " )" << std::endl; //function g

		std::cout << "lambda = " << lambda << std::endl;

		std::cout << "f(x) = " << func(xnew) << std::endl;

		grad_xn = gradient(xnew, func);
		//std::cout << "grad f(x) = ( " <<  grad_xn.get_v(0) << " ; " << grad_xn.get_v(1) << " )"<< std::endl; //function f
		std::cout << "grad f(x) = ( " << grad_xn.get_v(0) << " ; " << grad_xn.get_v(1) << ";" << grad_xn.get_v(2) << " )" << std::endl; //function g

		std::cout << "||grad f(x)|| = " << xnew.laenge(gradient(xnew, func)) << std::endl << std::endl; //Lenght from gradient


		xtest = lambda * grad_xn; //giving the new vector to a new variable to test with
		xtest = xtest + xnew; //x1 = x0 + lambda * grad f(xo)
		//std::cout << "x_neu = ( " << xtest.get_v(0) << " ;  " << xtest.get_v(1) << " )" << std::endl;   //Value after a step f function
		std::cout << "x_neu = ( " << xtest.get_v(0) << " ;  " << xtest.get_v(1) << " ; " << xtest.get_v(2) << " )" << std::endl;  //Value after a step g function

		std::cout << "f(x_neu) = " << func(xtest) << std::endl << std::endl;


		//Doppelte Schrittweite
		if (func(xtest) > func(xnew)) //xtest needs to be bigger than xnew(value from the loop before)
		{
			std::cout << "Test mit doppelter Schrittweite (lambda = " << 2 * lambda << " ) : " << std::endl;
			lambdatest = 2 * lambda;

			xprevtea = xtest; //saving the test value in case we can keep our old step width
			xtest = lambdatest * grad_xn; //giving the new vector to a new variable to test with
			xtest = xtest + xnew; //x1 = x0 + lambda * grad f(xo)
			//std::cout << "x_test = ( " << xtest.get_v(0) << " ; " << xtest.get_v(1) << " )" << std::endl;  //Value f function
			std::cout << "x_test = ( " << xtest.get_v(0) << " ; " << xtest.get_v(1) << " ; " << xtest.get_v(2) << " )" << std::endl; //Value g function
			std::cout << "f(x_test) = " << func(xtest) << std::endl;

			if (func(xprevtea) > func(xtest)) //in case that the previous step is lower than the test step
			{
				std::cout << "behalte alte Schrittweite!" << std::endl << std::endl;
				//lambdatest stays the same
				xnew = xprevtea; //resets xnew to the previous step
				grad_xn = gradient(xnew, func);
			}

			else if (func(xprevtea) < func(xtest)) //in case that the test is now bigger than the previous step
			{
				std::cout << "verdoppele Schrittweite!" << std::endl << std::endl;

				lambda = lambdatest; //giving lambda the new value since we need to keep calculating with it
				xnew = xtest; //the test step was successfull and is now the new starting point
				grad_xn = gradient(xnew, func);
			}

		}


		//Halbiere Schrittweite
		else if (func(xtest) <= func(xnew))
		{
			do
			{
				lambda = lambda / 2; //we want to half lambda until we find the fitting value, that's why we don't need to safe lambda here to lambdatest

				std::cout << "halbiere Schrittweite (lambda = " << lambda << " ) : " << std::endl;

				xtest = lambda * grad_xn; //xtest new vector
				xtest = xtest + xnew; //x1 = x0 + lambda * grad f(xo), lambda and grad already in xtest saved

				//std::cout << "x_neu = ( " << xtest.get_v(0) << " ; " << xtest.get_v(1) << " )" << std::endl;  //Value f function
				std::cout << "x_neu = ( " << xprevtea.get_v(0) << " ; " << xprevtea.get_v(1) << " ; " << xprevtea.get_v(2) << " )" << std::endl; //Value g function
				std::cout << "f(x_neu) = " << func(xtest) << std::endl << std::endl;

			} while (func(xtest) < func(xnew));  //checking when we found the value that we need

			xnew = xtest;
			grad_xn = gradient(xnew, func);
		}

		if (grad_xn.laenge(grad_xn) < limit) //ending when ||grad f(x)||<1e-5
		{
			std::cout << std::endl;
			std::cout << "Ende wegen ||grad f(x)||<1e-5 bei " << std::endl;
			//std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) << " )" << std::endl; //function f
			std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) << " ; " << xnew.get_v(2) << " )" << std::endl; //function g
			std::cout << "lambda = " << lambda << std::endl;
			std::cout << "f(x) = " << func(xnew) << std::endl;
			grad_xn = gradient(xnew, func);
			//std::cout << "grad f(x) = ( " << grad_xn.get_v(0) << " ; " << grad_xn.get_v(1) << " )" << std::endl; //function f
			std::cout << "grad f(x) = ( " << grad_xn.get_v(0) << " ; " << grad_xn.get_v(1) << " ; " << grad_xn.get_v(2) << " )" << std::endl; //function g
			std::cout << "||grad f(x)|| = " << xnew.laenge(gradient(xnew, func)) << std::endl << std::endl;
		}

		else if (step >= 25)
		{
			std::cout << std::endl;
			std::cout << "Ende wegen Schrittzahl = 25 bei " << std::endl; //ending when stepcount 25
			//std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) << " )" << std::endl; //function f
			std::cout << "x = " << "( " << xnew.get_v(0) << " ; " << xnew.get_v(1) << " ; " << xnew.get_v(2) << " )" << std::endl; //function g
			std::cout << "lambda = " << lambda << std::endl;
			std::cout << "f(x) = " << func(xnew) << std::endl;
			grad_xn = gradient(xnew, func);
			//std::cout << "grad f(x) = ( " << grad_xn.get_v(0) << " ; " << grad_xn.get_v(1) << " )" << std::endl; //function f
			std::cout << "grad f(x) = ( " << grad_xn.get_v(0) << " ; " << grad_xn.get_v(1) << " ; " << grad_xn.get_v(2) << " )" << std::endl; //function g
			std::cout << "||grad f(x)|| = " << xnew.laenge(gradient(xnew, func)) << std::endl << std::endl;
		}

		step++;

	} while (step < 25 && grad_xn.laenge(grad_xn) > limit); //setting the boundaries how long it should run: 25 steps or when value 10^-5

	return xnew;

}
