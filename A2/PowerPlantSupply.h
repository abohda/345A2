/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef POWERPLANTSUPPLY_H
#define POWERPLANTSUPPLY_H

#include "PowerPlant.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <ctime> 
#include <cstdlib>
#include <fstream>

#define NUM_POWERPLANTS 42
#define MARKET_SIZE 8

class PowerPlantSupply {
private:
	vector<PowerPlant> supply;
	vector<PowerPlant> market;
public:
	PowerPlantSupply();

	PowerPlant* getMarketPlantAt(int index);

	void addToSupply(PowerPlant *pp);
	void addToMarket();
	void shuffleSupply();
	bool sell(int index, Player *p, int price);

	void printPlantSupply();

	void savePPSContents(ofstream& ofs);
	void loadPPSContents(ifstream& ifs);
};

#endif