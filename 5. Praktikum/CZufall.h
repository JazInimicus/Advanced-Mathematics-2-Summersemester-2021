#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

class CZufall
{
public:
	int wert(int a, int b) { return rand() % (b - a + 1) + a; } //a <= n <= b

	//v1 = rand() % 100;         // v1 in the range 0 to 99
	//v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
	//v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 


	void initialisiere(int s) { srand(s); }

	std::vector<int> test(int a, int b, int N);

	std::vector<int> test_falsch(int a, int b, int N);

};

