#include "CMyMatrix.h"
#include "CMyVektor.h"



CMyMatrix::CMyMatrix()
{
	dimx = 0;
	dimy = 0;
	matrix.resize(0, std::vector<double>(0));
}


CMyMatrix::CMyMatrix(int x, int y) //Constructor
{
	dimx = x;
	dimy = y;
	matrix.resize(x, std::vector<double>(y));
}

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


CMyVektor operator*(CMyMatrix A, CMyVektor x)
{
	CMyVektor xvec(x.get_d());
	CMyMatrix Amat(A.get_Dimx(), A.get_Dimy());
	double ax = 0;

	if (xvec.get_d() != Amat.get_Dimx())
	{
		std::cout << "Dimensionen stimmen nicht überein!" << std::endl;
	}

	CMyVektor value(x.get_d());


	for (int i = 0; i < Amat.get_Dimx(); i++) //Rows
	{
		for (int j = 0; j < Amat.get_Dimy(); j++) //Colums
		{
			ax += A.get_v(i, j) * x.get_v(j);
		}
		value.set_v(i, ax); //sets the whole value from one row
		ax = 0; //Setting back to 0 for next loop
	}

	return value;
}


CMyMatrix invers(CMyMatrix A)
{
	CMyMatrix inv(2, 2);
	CMyMatrix matrix(2, 2);
	matrix = A;

	if (matrix.get_Dimx() != 2 && matrix.get_Dimy() != 2)
	{
		std::cout << "Keine 2x2 Matrix!" << std::endl;
		exit(3);
	}

	//det = ad - bc
	double det = (matrix.get_v(0, 0) * matrix.get_v(1, 1)) - (matrix.get_v(1, 0) * matrix.get_v(0, 1));

	inv.set_v(0, 0, (1 / det) * matrix.get_v(1, 1));
	inv.set_v(1, 0, (-1 / det) * matrix.get_v(1, 0));
	inv.set_v(0, 1, (-1 / det) * matrix.get_v(0, 1));
	inv.set_v(1, 1, (1 / det) * matrix.get_v(0, 0));

	return inv;
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


CMyVektor func(CMyVektor x) //R4->R3
{
	CMyVektor value(3);

	value.set_v(0, x.get_v(0) * x.get_v(1) * exp(x.get_v(2)));
	value.set_v(1, x.get_v(1) * x.get_v(2) * x.get_v(3));
	value.set_v(2, x.get_v(3));

	return value;
}

CMyVektor func2(CMyVektor x) //R2->R2
{
	CMyVektor value(2);
	value.set_v(0, (x.get_v(0) * x.get_v(0) * x.get_v(0)) * (x.get_v(1) * x.get_v(1) * x.get_v(1)) - 2 * x.get_v(1));
	value.set_v(1, x.get_v(0) - 2);

	return value;
}


/*CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	double const h = 1e-4;

	CMyVektor fx = funktion(x);
	int dimf = fx.get_d();
	int dimx = x.get_d();

	CMyMatrix jac(dimx, dimf);
	CMyVektor value(x);
	double v = 0.0;
	CMyVektor gradf(4);

	for (int i = 0; i < dimx; i++) //g = ((f(xi+h), xn) - f(xn)/h) || f(x0,y0,z0) = (f(x0+h, y0, z0) - f(x0,y0,z0))/h -> +h jeweils noch für die Funktion die man gerade ableitet
	{
		v = x.get_v(i); //Saving the value
		x.set_v(i, v + h);
		gradf.set_v(i, funktion(x).get_v(i));

		x.set_v(i, v); //Setting the value back to it's original value

		gradf.set_v(i, (gradf.get_v(i) - fx.get_v(i)) / h); //grad per row


		for (int j = 0; j < dimf; j++)
		{
			jac.set_v(i, j, gradf.get_v(j));
		}
	}

	return jac;
}*/


CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	double const h = 1e-4;

	int dimf = funktion(x).get_d();
	int dimx = x.get_d();

	CMyMatrix jac(dimf, dimx);

	CMyVektor xk = x; //Copy from x

	for (int i = 0; i < dimf; i++) //Rows
	{
		for (int j = 0; j < dimx; j++) //Columns
		{
			xk = x;

			xk.set_v(j, xk.get_v(j) + h); //value + h

			jac.set_v(i, j, (funktion(xk).get_v(i) - funktion(x).get_v(i)) / h);
		}
	}

	return jac;
}


void newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	double limit = 1e-5;
	int step = 0;

	CMyVektor xn = x;
	CMyVektor fxn = funktion(x);
	CMyVektor dx(2);

	CMyMatrix df(2, 2); //Saves jacobi Matrix and inverse Matrix

	double length = 0.0;

	do
	{
		std::cout << "Schritt " << step++ << ": " << std::endl;

		std::cout << "\t x = ( " << xn.get_v(0) << " ; " << xn.get_v(1) << " ) " << std::endl; //Starting Point

		std::cout << "\t f(x) = ( " << fxn.get_v(0) << " ; " << fxn.get_v(1) << " ) " << std::endl;

		df = jacobi(xn, func2);

		std::cout << "\t f'(x) = ( " << df.get_v(0, 0) << " ; " << df.get_v(0, 1) << std::endl << df.get_v(1, 0) << " ; " << df.get_v(1, 1) << " ) " << std::endl;

		df = invers(df);

		std::cout << "\t ((f'(x))^(-1) = ( " << df.get_v(0, 0) << " ; " << df.get_v(0, 1) << std::endl << df.get_v(1, 0) << " ; " << df.get_v(1, 1) << " ) " << std::endl;

		//delta x = -(J(xn)^-1*f(xn))

		dx = df * ((-1) * fxn);

		/*dx = -1 * fxn;
		dx = df * dx;*/

		std::cout << "\t dx = ( " << dx.get_v(0) << " ; " << dx.get_v(1) << " ) " << std::endl;

		length = fxn.laenge(fxn);

		std::cout << "\t ||f(x)|| = " << length << std::endl << std::endl;

		xn = xn + dx;
		fxn = funktion(xn);

	} while (xn.laenge(fxn) > limit && step < 50);


	if (xn.laenge(fxn) < limit)
	{
		std::cout << "Ende wegen ||f(x)||<1e-5 bei" << std::endl;
		std::cout << "\t x = ( " << xn.get_v(0) << " ; " << xn.get_v(1) << " ) " << std::endl;
		std::cout << "\t f(x) = ( " << fxn.get_v(0) << " ; " << fxn.get_v(1) << " ) " << std::endl;
		length = fxn.laenge(fxn);

		std::cout << "\t ||f(x)|| = " << length << std::endl;
	}


	else if (step >= 50)
	{
		std::cout << "Ende wegen Schrittzahl = 50 bei" << std::endl;
		std::cout << "\t x = ( " << xn.get_v(0) << " ; " << xn.get_v(1) << " ) " << std::endl;
		std::cout << "\t f(x) = ( " << fxn.get_v(0) << " ; " << fxn.get_v(1) << " ) " << std::endl;
		length = fxn.laenge(fxn);

		std::cout << "\t ||f(x)|| = " << length << std::endl;
	}

}
