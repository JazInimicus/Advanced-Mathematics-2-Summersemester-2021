#include <iostream>
#include "CKomplex.h"

int main()
{
	int input = 0;

	std::cout << "1 - Test Addition zweier komplexer Zahlen" << std::endl;
	std::cout << "2 - Test Multiplikation zweier komplexer Zahlen" << std::endl;
	std::cout << "3 - Test Multiplikation komplexer Zahlen mit double" << std::endl;
	std::cout << "4 - Test Aufgabe 2" << std::endl;
	std::cout << "5 - Ausgabe von Epsilon" << std::endl;
	std::cout << "6 - Maximale Abweichung" << std::endl;

	CKomplex komp1(2, 3);
	CKomplex komp2(4, 1);

	std::cin >> input;

	switch (input)
	{
	case 1:
	{
		CKomplex add = komp1 + komp2;
		std::cout << add.re() << " + " << add.im() << std::endl;

		break;
	}

	case 2:
	{
		CKomplex mult = komp1 * komp2;
		std::cout << mult.re() << " + " << mult.im() << std::endl;

		break;
	}

	case 3:
	{
		CKomplex mult = komp1 * 2;
		std::cout << mult.re() << " + " << mult.im() << std::endl;

		break;
	}

	case 4:
	{
		std::vector<CKomplex> values = werte_einlesen("Daten_original.txt");
		werte_ausgeben("test1.txt", values, 10);
	}

	case 5:
	{
		std::vector<CKomplex> values_O = werte_einlesen("Daten_original.txt");


		std::vector<CKomplex> values_FT = f_transformation(values_O, false);
		werte_ausgeben("DatenF1.txt", values_FT, -1.0);

		std::vector<CKomplex> values_FT_inv = f_transformation(werte_einlesen("DatenF1.txt"), true);
		werte_ausgeben("DatenF1inv.txt", values_FT_inv, -1.0);



		std::vector<CKomplex> values_FT2 = f_transformation(values_O, false);
		werte_ausgeben("DatenF2.txt", values_FT2, 0.001);

		std::vector<CKomplex> values_FT2_inv = f_transformation(werte_einlesen("DatenF2.txt"), true);
		werte_ausgeben("DatenF2inv.txt", values_FT2_inv, 0.001);


		std::vector<CKomplex> values3_FT = f_transformation(values_O, false);
		werte_ausgeben("DatenF3.txt", values_FT, 0.01);

		std::vector<CKomplex> values_FT3_inv = f_transformation(werte_einlesen("DatenF3.txt"), true);
		werte_ausgeben("DatenF3inv.txt", values_FT3_inv, 0.01);


		std::vector<CKomplex> values_FT4 = f_transformation(values_O, false);
		werte_ausgeben("DatenF4.txt", values_FT4, 0.1);

		std::vector<CKomplex> values_FT4_inv = f_transformation(werte_einlesen("DatenF4.txt"), true);
		werte_ausgeben("DatenF4inv.txt", values_FT4_inv, 0.1);


		std::vector<CKomplex> values_FT5 = f_transformation(values_O, false);
		werte_ausgeben("DatenF5.txt", values_FT5, 1.0);

		std::vector<CKomplex> values_FT5_inv = f_transformation(werte_einlesen("DatenF5.txt"), true);
		werte_ausgeben("DatenF5inv.txt", values_FT5_inv, 1.0);

		break;
	}

	case 6:
	{
		std::vector<CKomplex> values_O = werte_einlesen("Daten_original.txt");

		std::vector<CKomplex> values_FT = f_transformation(values_O, false);
		werte_ausgeben("DatenFur.txt", values_FT, -1.0);

		std::vector<CKomplex> test = werte_einlesen("DatenFur.txt");

		std::vector<CKomplex> values_FT_inv = f_transformation(test, true);
		//werte_ausgeben("DatenFinv.txt", values_FT_inv, -1.0);

		std::cout << "Maximale Abweichung bei Epsilon = -1.0 : " << difference(values_O, values_FT_inv) << std::endl;


		for (double epsilon = 0.001; epsilon < 2; epsilon *= 10)
		{
			std::vector<CKomplex> values_FT = f_transformation(values_O, false);
			werte_ausgeben("DatenFur.txt", values_FT, epsilon);

			std::vector<CKomplex> values_FT_inv = f_transformation(werte_einlesen("DatenFur.txt"), true);
			//werte_ausgeben("DatenFurinv.txt", values_FT_inv, epsilon);

			difference(values_FT, values_FT_inv);

			std::cout << "Maximale Abweichung bei Epsilon = " << epsilon << " : " << difference(values_O, values_FT_inv) << std::endl;
		}


		break;
	}
	}



	system("PAUSE");
	return 0;

}