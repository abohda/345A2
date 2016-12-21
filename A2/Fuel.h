/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef FUEL_H
#define FUEL_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Fuel {
private:
	string type;
	int quantity;
public:
	Fuel();
	Fuel(string type, int quantity);

	void addFuel(int amount);
	bool removeFuel(int amount);

	string getType();
	int getQuantity();

	void printFuel();

	void saveFuel(ofstream& ofs);
	void loadFuel(ifstream& ifs);
};

#endif