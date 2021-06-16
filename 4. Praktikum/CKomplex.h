#pragma once
#include <vector>
#include <math.h>

class CKomplex
{
private:
	double real = 0.0;
	double imag = 0.0;

public:
	CKomplex() //Standard Constructor
	{
		real = 0.0;
		imag = 0.0;
	}

	CKomplex(double a, double b) //Constructor
	{
		real = a;
		imag = b;
	}

	CKomplex(double phi) //Erzeugung von e^jphi
	{
		real = cos(phi);
		imag = sin(phi);
	}

	double re() { return real; }
	double im() { return imag; }

	double abs() { return sqrt(real * real + imag * imag); } //Betrag
};

CKomplex operator+(CKomplex a, CKomplex b);
CKomplex operator-(CKomplex a, CKomplex b);
CKomplex operator*(CKomplex a, CKomplex b);
CKomplex operator*(CKomplex a, double b);
CKomplex operator*(double b, CKomplex a);

double difference(std::vector<CKomplex> a, std::vector<CKomplex> b);

std::vector<CKomplex> f_transformation(std::vector<CKomplex> a, bool trans);

std::vector<CKomplex>  werte_einlesen(const char* dateiname);
void werte_ausgeben(const char* dateiname, std::vector<CKomplex> werte, double epsilon); //Epsilon: f.e. 1.0 : only values over 1.0 

