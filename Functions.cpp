#include <iostream>
#include <cmath>
#include <fstream>
#include <cassert>
#include "Comb_Calc.h"
using namespace std;


double Water_Vapor_P(double Tin) {		//Esta funcion calcula la presion de saturacion del agua a una temperatura dada
	double Pv = 0;
	double P[40], T[40];

	ifstream read_file ("sat_wat_temp.dat");
	assert(read_file.is_open());
	for (int i = 0; i <= 40; i++){
		read_file >> T[i] >> P[i];
	}
	
	for (int i = 0; i<=39; i++){
		
		if (Tin == T[i]){
			Pv = P[i];
			break;
		}
		
		else if (Tin < T[i]){
			Pv = (Tin - T[i-1]) * (P[i] - P[i-1]) / (T[i]-T[i-1]) + P[i-1];
			break;
		}

		else {
			continue;
		}
		
	}

	return Pv;
}

double Water_Vapor_T(double Pin) {		//Esta funcion calcula la temperatura de saturacion del agua a una presion dada
	double Tv = 0;
	double P[40], T[40];

	ifstream read_file ("sat_wat_temp.dat");
	assert(read_file.is_open());
	
	for (int i = 0; i <= 40; i++){
		read_file >> T[i] >> P[i];
	}
	
	for (int i = 0; i<=39; i++){
		
		if (Pin == P[i]){
			Tv = T[i];
			break;
		}
		
		else if (Pin < P[i]){
			Tv = (Pin - P[i-1]) * (T[i] - T[i-1]) / (P[i]-P[i-1]) + T[i-1];
			break;
		}

		else {
			continue;
		}
		
	}
	
	return Tv;
}

void Loop_calculos() {

	Comb_Calc Combustion;

	if (Combustion.ij == 1) {
		Combustion.Heat_Calc();
	}

	else if (Combustion.ij == 2) {
		Combustion.Heat_Calc_w_humid();
	}
	
	else if (Combustion.ij == 3) {
		Combustion.Adiab_Temp();	//This is new
	}
	
	else {
		cout << "\nDude what you just typed?\n";
	}

}
