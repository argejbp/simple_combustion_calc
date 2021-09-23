#include <iostream>
#include "Comb_Calc.h"
#include "Functions.h"
using namespace std;


int main() {

	cout << "Hecho Por Argenis Bonilla, Cuarentena Covid19 2020\n\n";
	cout << "Programa para calculos de combustion\nSuposiciones realizadas:" << endl;
	cout << "Comportamiento de Gas Ideal del aire y los productos de combustion" << endl;
	cout << "Combustible de hidrocarburos (Un solo combustible en la reaccion)" << endl;
	cout << "Se utilizan polinomios de aproximacion para el calor especifico como funcion de la temperatura" << endl;
	cout << "Proceso isobarico, P = 1 atm\n\n";
	cout << "La temperatura de entrada del aire y la temperatura de entrada \ndel combustible son independiente una de la otra, y pueden modificarse" << endl;

	system("pause");
	int a = 1;

	do {

		Loop_calculos();

		cout << "\n\n¿Quieres realizar otro calculo?";
		cout << "\n[0] No ";
		cout << "\n[1] Si ";
		cout << "\nSu eleccion: ";
		cin >> a;
		
	} while (a!= 0);

}
