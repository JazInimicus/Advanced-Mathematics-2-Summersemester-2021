#include "CMyVektor.h"
#include "C_DGLSolver.h"


CMyVektor::CMyVektor()
{
	dimension = 0;
	vektor.resize(dimension);
}

CMyVektor::CMyVektor(int x)
{
	dimension = x;
	vektor.resize(dimension);
}


//addition operator
CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	CMyVektor addition(a.get_d());


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
	CMyVektor multiplikation(a.get_d());


	for (int i = 0; i < a.get_d(); i++)
	{
		double la = lambda * a.get_v(i);
		multiplikation.set_v(i, la);
	}

	return multiplikation;
}



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



CMyVektor f1(CMyVektor y, double x)
{
	CMyVektor result(2);

	result.set_v(0, 2 * y.get_v(1) - x * y.get_v(0)); //y1' = 2 * y2 - x * y1
	result.set_v(1, y.get_v(0) * y.get_v(1) - 2 * x * x * x); //y2' = y1 * y2 - 2 x^3

	return result;
}

double f2(CMyVektor y, double x)
{
	return (2 * x * y.get_v(1) * y.get_v(2)) + (2 * (y.get_v(0) * y.get_v(0)) * y.get_v(1)); //2 * x * y' * y'' + 2 * y * y * y'
}




//Ableitung f(xo+h)-f(xo) / h ODER f(x)-f(xo) / x-x0

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{
	if (!DGL_nterorder)
	{
		return f_DGL_System(y, x);
	}

	int dim = y.get_d();
	CMyVektor ableitung(dim);

	for (int i = 1; i < dim; i++)
	{
		//ableitung.set_v(i - 1, ableitung.get_v(i));
		ableitung.set_v(i - 1, y.get_v(i));

		//y'0 = (y)' = y' = y1
		//y'1 = (y')' = y'' = y2
	}

	ableitung.set_v(dim - 1, f_DGL_nterOrdnung(y, x)); //last position calculation
	return ableitung;
}



/*Euler-Verfahren:
	y(x1) = y(xo+h) = y(xo) + h*f(xo,yo)
	y(x2) = y(x1+h) = y(x1) + h*f(x1,y(x1))
	y(x3) = y(x2+h) = y(x2) + h*f(x2,y(x2))
	h = Schrittweite
*/

CMyVektor C_DGLSolver::euler(double start, double end, int steps, CMyVektor y_Start)
{
	double x = start;
	CMyVektor y = y_Start;
	CMyVektor ya(y_Start.get_d());
	double h = (end - start) / steps;

	for (int i = 0; i < steps; i++)
	{
		ya = ableitungen(y, x);

		std::cout << "Schritt " << i << std::endl;
		std::cout << "		x = " << x << std::endl;
		std::cout << "		y = ( " << y.get_v(0) << " ; " << y.get_v(1) << " ) " << std::endl;
		std::cout << "		y' = ( " << ya.get_v(0) << " ; " << ya.get_v(1) << " ) " << std::endl << std::endl;

		y = y + h * ya;
		x += h;

		if (i + 1 == steps)
		{
			std::cout << "Ende bei : " << std::endl;
			std::cout << "		x = " << x << std::endl;
			std::cout << "		y = ( " << y.get_v(0) << " ; " << y.get_v(1) << " ) " << std::endl;
		}
	}

	return y;
}

CMyVektor C_DGLSolver::heun(double start, double end, int steps, CMyVektor y_Start)
{
	double x = start;
	CMyVektor y = y_Start;
	CMyVektor ya(y_Start.get_d());
	double h = (end - start) / steps;

	CMyVektor yt = y; //y Test
	CMyVektor yat = ya; //y Ableitung Test
	CMyVektor yam = ya; //y Ableitung Mittel


	for (int i = 0; i < steps; i++)
	{
		std::cout << "Schritt " << i << std::endl;
		std::cout << "		x = " << x << std::endl;
		std::cout << "		y = ( " << y.get_v(0) << " ; " << y.get_v(1) << " ) " << std::endl;

		ya = ableitungen(y, x);

		std::cout << "		y'_orig = ( " << ya.get_v(0) << " ; " << ya.get_v(1) << " ) " << std::endl << std::endl;

		x += h;
		yt = y + h * ya;
		yat = ableitungen(yt, x);
		yam = 0.5 * (ya + yat);

		std::cout << "		y_Test = ( " << yt.get_v(0) << " ; " << yt.get_v(1) << " ) " << std::endl;
		std::cout << "		y'_Test = ( " << yat.get_v(0) << " ; " << yat.get_v(1) << " ) " << std::endl << std::endl;

		std::cout << "		y'_Mittel = ( " << yam.get_v(0) << " ; " << yam.get_v(1) << " ) " << std::endl << std::endl;


		y = y + h * yam;
		//x += h;

		if (i + 1 == steps)
		{
			std::cout << "Ende bei : " << std::endl;
			std::cout << "		x = " << x << std::endl;
			std::cout << "		y = ( " << y.get_v(0) << " ; " << y.get_v(1) << " ) " << std::endl;
		}
	}

	return y;
}




CMyVektor C_DGLSolver::euleroA(double start, double end, int steps, CMyVektor y_Start)
{
	double x = start;
	CMyVektor y = y_Start;
	CMyVektor ya(y_Start.get_d());
	double h = (end - start) / steps;

	for (int i = 0; i < steps; i++)
	{
		ya = ableitungen(y, x);

		y = y + h * ya;
		x += h;
	}

	return y;
}




CMyVektor C_DGLSolver::heunoA(double start, double end, int steps, CMyVektor y_Start)
{
	double x = start;
	CMyVektor y = y_Start;
	CMyVektor ya(y_Start.get_d());
	double h = (end - start) / steps;

	CMyVektor yt = y; //y Test
	CMyVektor yat = ya; //y Ableitung Test
	CMyVektor yam = ya; //y Ableitung Mittel


	for (int i = 0; i < steps; i++)
	{
		ya = ableitungen(y, x);

		x += h;
		yt = y + h * ya;
		yat = ableitungen(yt, x);
		yam = 0.5 * (ya + yat);

		y = y + h * yam;
		//x += h;
	}

	return y;
}
