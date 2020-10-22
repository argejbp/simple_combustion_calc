using namespace std;
#include "Functions.h"

class Comb_Calc {
	
private:
	
	double AC, ath, e;
	double alpha, beta, gamma;
	double EA, f, phi, fs;
	double Ti, Te, Tfa, Tic;
	double Hr, Hp, Hc, Q;
	double Pi, Value;
	double Tv, Pv;
	Fuel Combustible;
	Gas O2, CO2, N2, H2O;

public:

	int ii, ij;
	
	Comb_Calc();
	void RecibeDatos(int i);
	void Heat_Calc();
	void Heat_Calc_w_humid();
	void Adiab_Temp();	//Now working yet
	double Fuel_Enthalpy(double T, int type);
	double gas_enthalpy(double Tg, int type);

};
