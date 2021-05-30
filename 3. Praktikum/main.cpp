#include <iostream>
#include "CMyVektor.h"
#include "C_DGLSolver.h"

int main()
{
	int input = 0;

	std::cout << "1 - Euler - Verfahren" << std::endl;
	std::cout << "2 - Heun - Verfahren" << std::endl;
	std::cout << "3 - Abweichung" << std::endl;

	std::cin >> input;



	double x1s = 0; double x1e = 2;
	int step1 = 100;
	CMyVektor y1s(2);
	C_DGLSolver s1 = C_DGLSolver(f1);

	y1s.set_v(0, 0);
	y1s.set_v(1, 1);


	switch (input)
	{

	case 1:
	{
		std::cout << "Euler - Verfahren : " << std::endl << std::endl;
		s1.euler(x1s, x1e, step1, y1s);

		break;
	}

	case 2:
	{
		std::cout << "Heun - Verfahren : " << std::endl << std::endl;
		s1.heun(x1s, x1e, step1, y1s);

		break;
	}


	case 3:
	{
		double x2s = 1; double x2e = 2;
		int step2[4] = { 10, 100, 1000, 10000 };
		CMyVektor y2s(3);
		C_DGLSolver s2 = C_DGLSolver(f2);

		y2s.set_v(0, 1); y2s.set_v(1, -1); y2s.set_v(2, 2);

		for (int i = 0; i < 4; i++)
		{
			std::cout << "Abweichung bei Euler bei " << step2[i] << " Schritten : " << s2.euleroA(x2s, x2e, step2[i], y2s).get_v(0) - 0.5 << std::endl;
			std::cout << "Abweichung bei Heun bei " << step2[i] << " Schritten : " << s2.heunoA(x2s, x2e, step2[i], y2s).get_v(0) - 0.5 << std::endl;

		}

		break;
	}
	}


	system("PAUSE");
	return 0;
}