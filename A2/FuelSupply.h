/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef FUELSUPPLY_H
#define FUELSUPPLY_H

#include "Fuel.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class FuelSupply {
private:
	vector<Fuel> supply;
	vector<Fuel> market;
public:
	FuelSupply();

	vector<Fuel> getSupply();
	vector<Fuel> getMarket();

	void addToSupply(Fuel *f);
	void addToMarket(Fuel *f);
	void addToMarket(string type, int quantity);
	bool sell(int index, int amount, Player *p);

	void printFuelSupply();

	void saveFSContents(ofstream& ofs);
	void loadFSContents(ifstream& ifs);
};

#endif