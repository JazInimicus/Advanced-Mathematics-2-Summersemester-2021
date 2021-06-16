#include <iostream>
#include <fstream>
#include "CKomplex.h"

using namespace std;

CKomplex operator+(CKomplex a, CKomplex b)
{
	return CKomplex(a.re() + b.re(), a.im() + b.im());
}

CKomplex operator-(CKomplex a, CKomplex b)
{
	return CKomplex(a.re() - b.re(), a.im() - b.im());
}



CKomplex operator*(CKomplex a, CKomplex b)
{
	// z1 = x1 + iy1, z2 = x2 + iy2
	//z1* z2 = (x1x2 - y1y2) + i(x1y2 + x2y1)

	//(x1+y1i) * (x2+y2i)
  // = x1*x2 + x1*y2i + x2*y1i + y1*y2i^2
  // => i^2 = -1
  // x1*x2 + x1*y2i + x2*y1i -y1*y2
  // => zusammenfassen in real und imag teil:
  // = (x1*x2-y1*y2)+(x1*y2+x2*y1)*i

	return CKomplex(a.re() * b.re() - a.im() * b.im(), a.re() * b.im() + a.im() * b.re());
}


CKomplex operator*(CKomplex a, double b)
{
	return CKomplex(a.re() * b, a.im() * b);
}

CKomplex operator*(double b, CKomplex a)
{
	return CKomplex(a.re() * b, a.im() * b);
}



std::vector<CKomplex> f_transformation(std::vector<CKomplex> a, bool trans)
{


	int N = a.size(); //Values in Vector
	std::vector<CKomplex> result(N);

	const double pi = 3.14159265358979323846;

	int inv = 0;
	if (!trans) //fourier transformation
	{
		inv = -1;
	}

	else //fourier back transformation
	{
		inv = 1;
	}

	CKomplex tmp(0, 0);
	for (int n = 0; n < N; n++) //running through .txt values
	{
		tmp = CKomplex(0, 0);

		for (int k = 0; k < N; k++) //k = 0, N-1
		{
			tmp = tmp + (a[k] * CKomplex((inv * (2 * pi * k * n) / N))); //fk * e^+/-(j*2pi*k*n/N)
		}

		result[n] = (1 / sqrt(N)) * tmp;
	}

	return result;
}


double difference(std::vector<CKomplex> a, std::vector<CKomplex> b)
{
	int N = a.size();
	double max = 0.0;
	double dif = 0.0;

	for (int i = 0; i < N; i++)
	{
		dif = (a[i] - b[i]).abs();

		if (dif > max)
		{
			max = dif;
		}
	}
	return max;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//.............................................Hoever functions start.............................................//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<CKomplex>  werte_einlesen(const char* dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char* dateiname, vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << std::endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << std::endl;
	// File schliessen
	fp.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//................................................Hoever functions ends...........................................//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////