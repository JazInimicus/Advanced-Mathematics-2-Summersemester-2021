#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "CZufall.h"

int main()
{
	int input = 0;

	int a = 3, b = 7, N = 10000;
	std::vector<int> value;

	CZufall z;
	z.initialisiere(0);

	std::cin >> input;

	switch (input)
	{
	case 1: //same value for s
	{
		for (int i = 0; i < 4; ++i)
		{
			std::cout << "V " << i << " : " << std::endl;
			value = z.test(a, b, N);

			for (int j = 0; j < value.size(); ++j)
			{
				std::cout << j << " : " << value[j] << std::endl;
			}

			std::cout << std::endl;
		}

	}
	}

	system("PAUSE");
	return 0;
}