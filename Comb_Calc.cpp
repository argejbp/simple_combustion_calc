#include <iostream>
#include <cmath>
#include <fstream>
#include <cassert>

#include "Functions.h"
#include "Comb_Calc.h"
using namespace std;

const int Tr = 298;				//Temperatura de referencia [K]


	Comb_Calc::Comb_Calc() {			//El constructor de la clase Comb_Calc recibe los valores principales necesarios para los calculos posteriores


		cout << "\n\n1) Calculo de Calor de Combustion \n2) Calculo de Calor de Combustion con Aire Humedo \n3) Calculo de Temperatura de Flama Adiabatica\nSu opcion de calculo: ";
		cin >> ij;

		RecibeDatos(ij);				//Llamada a funcion que recibe los datos de la reaccion

		alpha = Combustible.a;
		beta = Combustible.b;
		gamma = Combustible.c;
		double Mf = Combustible.MMC;
		double Ma = 28.84;
		int i;

		ath = (alpha + beta / 4 - gamma / 2);
		fs = Mf / (ath*4.76*Ma);

		cout << "\nIndique la variable conocida: \n1) Porcentaje de aire en exceso\n2) Relacion Aire-Combustible\n3) Relacion de equivalencia\nSu eleccion: ";
		cin >> i;

		switch (i) {

			case 1:

				cout << "\nIngrese el porcentaje de aire en exceso: ";
				cin >> EA;

				f = 100 * fs / (EA + 100);
				AC = 1 / f;
				phi = 100 / (EA + 100);

				break;

			case 2:

				cout << "\nIngrese la relacion Aire-Combustible: ";
				cin >> AC;

				f = 1 / AC;
				phi = f / fs;
				EA = 100 * (1 - phi) / phi;

				break;

			case 3:

				cout << "\nIngrese la relacion de equivalencia: ";
				cin >> phi;

				f = fs * phi;
				AC = 1 / f;
				EA = 100 * (1 - phi) / phi;

				break;

		}
		
		O2.hfg = 0.0;
		O2.hs = 8682;

		CO2.hfg = -393520;
		CO2.hs = 9364;

		N2.hfg = 0;
		N2.hs = 8669;

		H2O.hfg = -241820;
		H2O.hs = 9904;
	}

	void Comb_Calc::RecibeDatos(int i) {

		cout << "\n\nIndique la temperatura del aire en la entrada de la camara de combustion en [K]: ";
		cin >> Ti;
		cout << "Indique la temperatura del combustible a la entrada de la camara de combustion en [K]: ";
		cin >> Tic;

		if (i == 1 || i == 2) {
			cout << "Indique la temperatura de salida de los productos de combustion en [K]: ";
			cin >> Te;
		
		}

		else if (i == 3) {
			cout << "Indique la primera suposicion de temperatura de flama adiabatica en [K]: ";
			cin >> Te;
		}
		


		cout << "\nIndique el combustible a utilizar: \n1) Metano \n2) Acetileno \n3) Etano \n4) Etanol \n5) Propano \nSu eleccion: ";
		cin >> ii;

		switch (ii) {

			case 1:								//Propiedades del Metano
				Combustible.MMC = 16.043;
				Combustible.PCI = 50050;
				Combustible.PCS = 55530;
				Combustible.hfc = -74850;
				Combustible.a = 1.0;
				Combustible.b = 4.0;
				Combustible.c = 0.0;
				break;

			case 2:								//Propiedades del Acetileno
				Combustible.MMC = 26.038;
				Combustible.PCI = 48280;
				Combustible.PCS = 49970;
				Combustible.hfc = 226730;
				Combustible.a = 2.0;
				Combustible.b = 2.0;
				Combustible.c = 0.0;
				break;

			case 3:								//Propiedades del Etano
				Combustible.MMC = 30.070;
				Combustible.PCI = 47520;
				Combustible.PCS = 51900;
				Combustible.hfc = -84680;
				Combustible.a = 2.0;
				Combustible.b = 6.0;
				Combustible.c = 0.0;
				break;

			case 4:								//Propiedades del Etanol
				Combustible.MMC = 46.069;
				Combustible.PCI = 26810;
				Combustible.PCS = 29670;
				Combustible.rho = 0.790;
				Combustible.hfc = -235120;
				Combustible.a = 2.0;
				Combustible.b = 6.0;
				Combustible.c = 1.0;
				break;

			case 5:								//Propiedades del Propano
				Combustible.MMC = 44.097;
				Combustible.PCI = 46340;
				Combustible.PCS = 50330;
				Combustible.rho = 0.5;
				Combustible.hfc = -103850;
				Combustible.a = 3.0;
				Combustible.b = 8.0;
				Combustible.c = 0.0;
				break;

			case 6:								//Propiedades del Butano
				Combustible.MMC = 58.123;
				Combustible.PCI = 45370;
				Combustible.PCS = 49150;
				Combustible.rho = 0.579;
				Combustible.hfc = -126150;
				Combustible.a = 4.0;
				Combustible.b = 10.0;
				Combustible.c = 0.0;
				break;
			

		}

		Combustible.hs = Fuel_Enthalpy(Tr, ii);

	}



	void Comb_Calc::Heat_Calc() {						//Cacula el calor liberado en la combustion con aire seco

		// Se calcula la entalpia de los reactivos a la temperatura de entrada
		// Entalpia del aire seco:
		Hr = ath * (EA / 100 + 1) * (O2.hfg + (gas_enthalpy(Ti, 4) - O2.hs) + 3.76*(N2.hfg + (gas_enthalpy(Ti, 2) - N2.hs)));
		// Entalpia del combustible:
		Hc = Combustible.hfc + (Fuel_Enthalpy(Tic, ii) - Combustible.hs);
		// Se calcula la entalpia de los productos a la temperatura de salida
		Hp = alpha * (CO2.hfg + (gas_enthalpy(Te, 1) - CO2.hs)) + 3.76 * ath * (EA / 100 + 1)*(N2.hfg + (gas_enthalpy(Te, 2) - N2.hs)) + (beta / 2)* (H2O.hfg + (gas_enthalpy(Te, 3) - H2O.hs)) + ath * EA / 100 * (O2.hfg + (gas_enthalpy(Te, 4) - O2.hs));	

		Q = Hc + Hr - Hp;

		cout << "\nEl Calor de Combustion es: " << Q << " kJ/kmol de combustible";
		cout << "\nLa entalpia de los productos de combustion es: " << Hp << " kJ/kmol de combustible";

	}

	void Comb_Calc::Heat_Calc_w_humid() {				//Cacula el calor liberado en la combustion con aire humedo
	
		double Nv, Pp, Td, Tsat, Psat, Xi, Pv, Pv_air;		
		double relative_humid;
		
		const double Ptotal = 101.325;

		cout << "\nIngrese la humedad relativa del aire atmosferico: ";
		cin >> relative_humid;

		//Metodologia de calculo para incluir la humdad del aire esta basada en ejercicio ejemplo 15-4 de Termodinamica - Yunus Cengel 7ma edicion

		Psat = Water_Vapor_P(Ti - 273.15);		//Se calcula la presion de saturacion del vapor de agua en pascal
		Pv_air = relative_humid*Psat;	//Se calcula la presion parcial del vapor de agua en el aire atmosferico en pascal

		Xi = Pv_air / Ptotal;	
		Nv = (4.76*ath*Xi) / (1 - Xi);	//Se calculan los moles de vapor de agua contenidos en el aire atmosferico
		Pv = Ptotal*(beta/2 + Nv) / (alpha + 3.76 * ath * (EA / 100 + 1) + beta/2 + ath * EA / 100);	//Se calcula la presion parcial de la humedad en los productos de combustion en kilopascal

		Tsat = Water_Vapor_T(Pv);	//Se calcula la temperatura de punto de rocio de los gases de combustion en ÂªC

		//Se realizan los calculos de calor de combustion incluyendo la humedad del aire

		// Se calcula la entalpia de los reactivos a la temperatura de entrada
		// Entalpia del aire seco:
		Hr = ath * (EA / 100 + 1) * (O2.hfg + (gas_enthalpy(Ti, 4) - O2.hs) + 3.76*(N2.hfg + (gas_enthalpy(Ti, 2) - N2.hs))) + Nv*(H2O.hfg + (gas_enthalpy(Ti, 3) - H2O.hs));
		// Entalpia del combustible:
		Hc = Combustible.hfc + (Fuel_Enthalpy(Tic, ii) - Combustible.hs);
		// Se calcula la entalpia de los productos a la temperatura de salida
		Hp = alpha * (CO2.hfg + (gas_enthalpy(Te, 1) - CO2.hs)) + 3.76 * ath * (EA / 100 + 1)*(N2.hfg + (gas_enthalpy(Te, 2) - N2.hs)) + (beta / 2 + Nv)* (H2O.hfg + (gas_enthalpy(Te, 3) - H2O.hs)) + ath * EA / 100 * (O2.hfg + (gas_enthalpy(Te, 4) - O2.hs));	

		Q = Hc + Hr - Hp;

		cout << "\nEl Calor de Combustion es: " << Q << " kJ/kmol de combustible";
		cout << "\nLa entalpia de los productos de combustion es: " << Hp << " kJ/kmol de combustible";
		cout << "\nLa temperatura de punto de rocio de los productos de combustion es: " << Tsat << " grados Celsius";
	}

	void Comb_Calc::Adiab_Temp() {		//Calcula la temperatura de flama adiabatica utilizando el Metodo de Biseccion

		double Eq = 0, Tad = 0, Ttest1 = 0, Ttest2 = 0, Hptest1 = 0, Hptest2 = 0, Eqtest1 = 0, Eqtest2 = 0;

		// Se calcula la entalpia de los reactivos a la temperatura de entrada
		// Entalpia del aire seco:
		Hr = ath * (EA / 100 + 1) * (O2.hfg + (gas_enthalpy(Ti, 4) - O2.hs) + 3.76*(N2.hfg + (gas_enthalpy(Ti, 2) - N2.hs)));
		// Entalpia del combustible:
		Hc = Combustible.hfc + (Fuel_Enthalpy(Tic, ii) - Combustible.hs);
		
		Ttest1 = 0.5*Te;
		Ttest2 = 1.5*Te;
		Tad = (Ttest1 + Ttest2)/2;

		int it = 0;

		do {
			
			Hptest1 = alpha * (CO2.hfg + (gas_enthalpy(Ttest1, 1) - CO2.hs)) + 3.76 * ath * (EA / 100 + 1)*(N2.hfg + (gas_enthalpy(Ttest1, 2) - N2.hs)) + (beta / 2)* (H2O.hfg + (gas_enthalpy(Ttest1, 3) - H2O.hs)) + ath * EA / 100 * (O2.hfg + (gas_enthalpy(Ttest1, 4) - O2.hs));
			Hptest2 = alpha * (CO2.hfg + (gas_enthalpy(Ttest2, 1) - CO2.hs)) + 3.76 * ath * (EA / 100 + 1)*(N2.hfg + (gas_enthalpy(Ttest2, 2) - N2.hs)) + (beta / 2)* (H2O.hfg + (gas_enthalpy(Ttest2, 3) - H2O.hs)) + ath * EA / 100 * (O2.hfg + (gas_enthalpy(Ttest2, 4) - O2.hs));
			Hp = alpha * (CO2.hfg + (gas_enthalpy(Tad, 1) - CO2.hs)) + 3.76 * ath * (EA / 100 + 1)*(N2.hfg + (gas_enthalpy(Tad, 2) - N2.hs)) + (beta / 2)* (H2O.hfg + (gas_enthalpy(Tad, 3) - H2O.hs)) + ath * EA / 100 * (O2.hfg + (gas_enthalpy(Tad, 4) - O2.hs));

			Eqtest1 = Hc + Hr - Hptest1;
			Eqtest2 = Hc + Hr - Hptest2;
			Eq = Hc + Hr - Hp;

			if (Eq > 0 || Eq < 0)
			{
				if (Eq*Eqtest1 > 0)
				{
					Ttest1 = Tad;
				}

				else if (Eq*Eqtest1 < 0)
				{
					Ttest2 = Tad;
				}

				it = it + 1;
				Tad = (Ttest1 + Ttest2)/2;
				
			}

			else if (Eq == 0)
			{
				/* boom you found the adiabatic flame temperature */
			}
			

		} while ( abs(Eq) > 1E-06 && it < 100 );
		
		if (abs(Eq) > 1E-03)
		{
			cout << "\nMejore la primera temperatura supuesta, no hubo convergencia";
		}
		cout << "\nQ = Hr - Hp = " << Eq << endl;
		cout << "La Temperatura de Flama Adiabatica es: " << Tad << " K";

	}

	double Comb_Calc::Fuel_Enthalpy(double T, int type) {			//Esta funcion calcula la entalpia del combustible

		double value_h, a, b, c, d;

		switch (type) {

			case 1:
				a = 19.89;
				b = 5.024E-02;
				c = 1.269E-05;
				d = -11.01E-09;
				break;

			case 2:
				a = 21.8;
				b = 9.2143E-02;
				c = -6.527E-05;
				d = 18.21E-09;
				break;

			case 3:
				a = 6.900;
				b = 17.27E-02;
				c = -6.406E-05;
				d = 7.285E-09;
				break;

			case 4:
				a = 19.9;
				b = 20.96E-02;
				c = -10.38E-05;
				d = 20.05E-09;
				break;

			case 5:
				a = -4.04;
				b = 30.48E-02;
				c = -15.72E-05;
				d = 31.74E-09;
				break;

			case 6:
				//Not read now
				break;
		}

		Combustible.Cpc = a + b * T + c * pow(T, 2.0) + d * pow(T, 3.0);	// Rango de temperatura para la cual es valida la expresion: 273 <= T(K) <= 1500
		value_h = Combustible.Cpc * T;
		return value_h;

	}

	double Comb_Calc::gas_enthalpy(double Tg, int type) {			//Esta funcion calcula la entalpia molar de un gas ideal, se incluye O2, CO2, N2, y H20
		double value_hg;
		double T[156], u[156], h[156], s[156];


		if (type == 1){
			ifstream read_file ("CO2_data.dat");
			assert(read_file.is_open());
			for (int i = 0; i <= 156; i++){
				read_file >> T[i] >> h[i] >> u[i] >> s[i];
			}
			
			read_file.close();
		}

		else if (type == 2){
			ifstream read_file ("nitrogen_data.dat");
			assert(read_file.is_open());
			for (int i = 0; i <= 156; i++){
				read_file >> T[i] >> h[i] >> u[i] >> s[i];
			}
			
		read_file.close();
		}
			
		else if (type == 3){
			ifstream read_file ("H2O_data.dat");
			assert(read_file.is_open());
			for (int i = 0; i <= 156; i++){
				read_file >> T[i] >> h[i] >> u[i] >> s[i];
			}
			
			read_file.close();
		}	

		else if (type == 4){
			ifstream read_file ("oxygen_data.dat");
			assert(read_file.is_open());
			for (int i = 0; i <= 156; i++){
				read_file >> T[i] >> h[i] >> u[i] >> s[i];
			}
			
			read_file.close();
		}
		
		else {
			cout << "Invalid input\n";
		}
		
		for (int i = 0; i <= 156; i++){
			if (Tg == T[i]){
				value_hg = h[i];
				break;
			}
			
			else if (Tg < T[i]){
				value_hg = (Tg-T[i-1]) * ( (h[i]-h[i-1]) / (T[i]-T[i-1]) ) + h[i-1];
				break;
			}
		}
	
		return value_hg;
	}
