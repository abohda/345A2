/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef POWERPLANT_H
#define POWERPLANT_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class PowerPlant {
private:
	string fuelType1;
	string fuelType2;
	int fuelAmount;
	int housesPowered;
	int value;
public:
	PowerPlant();
	PowerPlant(string type1, string type2, int value, int amount, int houses);

	string getType1();
	string getType2();
	int getAmount();
	int getNumberHouses();
	int getValue();

	void printPowerPlant();

	void savePowerPlant(ofstream& ofs);
	void loadPowerPlant(ifstream& ifs);
	string loadFuelType(ifstream& ifs);
};

#endif