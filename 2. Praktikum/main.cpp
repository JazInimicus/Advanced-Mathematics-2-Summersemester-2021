#include <iostream>
#include <math.h>
#include <vector>
#include "CMyMatrix.h"
#include "CMyVektor.h"

int main()
{
	//CMyVektor x(4);
	//CMyMatrix jacobim(4, 3);
	//x.set_v(0, 1.0); x.set_v(1, 2.0); x.set_v(2, 0.0); x.set_v(3, 3.0);

	//jacobim = jacobi(x, func);

	////output
	//std::cout << jacobim.get_v(0, 0) << " " << jacobim.get_v(0, 1) << " " << jacobim.get_v(0, 2) << " " << jacobim.get_v(0, 3) << std::endl;
	//std::cout << jacobim.get_v(1, 0) << " " << jacobim.get_v(1, 1) << " " << jacobim.get_v(1, 2) << " " << jacobim.get_v(1, 3) << std::endl;
	//std::cout << jacobim.get_v(2, 0) << " " << jacobim.get_v(2, 1) << " " << jacobim.get_v(2, 2) << " " << jacobim.get_v(2, 3) << std::endl;



	CMyVektor y(2);
	y.set_v(0, 1); y.set_v(1, 1);

	newton(y, func2);



	//Debugging
	/*CMyMatrix A(2, 2);
	CMyVektor x(2);
	CMyVektor s(2);

	A.set_v(0, 0, 1); A.set_v(0, 1, 1); A.set_v(1, 0, 1); A.set_v(1, 1, 1);
	x.set_v(0, 1); x.set_v(1, 1);

	s = A * x;

	std::cout << s.get_v(0) << " ; " << s.get_v(1) << std::endl;*/


	system("PAUSE");
	return 0;

}