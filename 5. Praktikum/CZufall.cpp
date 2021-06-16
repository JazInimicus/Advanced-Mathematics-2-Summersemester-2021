#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "CZufall.h"



std::vector<int> CZufall::test(int a, int b, int N)
{
	std::vector<int> result = std::vector<int>(b - a + 1, 0);
	int value = 0;

	for (int i = 0; i < N; i++)
	{
		value = wert(a, b);
		++result[value - a];
	}

	return result;
}

std::vector<int> CZufall::test_falsch(int a, int b, int N)
{
	std::vector<int> result = std::vector<int>(b - a + 1, 0);
	int value = 0;

	for (int i = 0; i < N; i++)
	{
		initialisiere(time(NULL));

		value = wert(a, b);
		++result[value - a];
	}

	return result;
}