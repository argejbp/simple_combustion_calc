#include <iostream>
using namespace std;

double Water_Vapor_P(double Tin);
double Water_Vapor_T(double Pin);
void Loop_calculos();


#ifndef Gas_H
#define Gas_H

struct Gas {
	double NM;				//Numero de Moles del Gas
	double MM;				//Masa molar del Gas
	double yi;				//Fraccion molar del Gas
	double fi;				//Fraccion masica del Gas
	double hfg;				//Entalpia de formacion del Gas
	double hs;				//Entalpia sensible en el estado de referencia (298 K, 1 atm)
	double value_ug;		//Energia interna del Gas (Gas ideal) interpolado
	double value_sg;		//Entropia del Gas (Gas ideal) interpolado
};

#endif

#ifndef Fuel_H
#define Fuel_H

struct Fuel {
	double PCI;				//Poder Calorifico Inferior del Combustible
	double PCS;				//Poder Calorifico Superior del Combustible
	double rho;				//Densidad del Combustible
	double MMC;				//Masa Molar del Combustible
	double hfc;				//Entalpia de formacion del Combustible
	double hs;				//Entalpia sensible en el estado de referencia (298 K, 1 atm)
	double Cpc;				//Calor Especifico a Presion Constante en funcion a la temperatura [kJ/kmol*K]
	double a;				//Numero de moles de Carbono en el combustible
	double b;				//Numero de moles de Hidrogeno en el combustible
	double c;				//Numero de moles de Oxigeno en el combustible
};

#endif


