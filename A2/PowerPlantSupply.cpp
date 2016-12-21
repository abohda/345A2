/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "PowerPlantSupply.h"

/*********** CONSTRUCTOR **********/

PowerPlantSupply::PowerPlantSupply() {
	market.resize(0);
}

/*********** GETTERS **********/

PowerPlant* PowerPlantSupply::getMarketPlantAt(int index) {
	return &market[index];
}

/*********** OTHER METHODS **********/

/* Used only in the construction of the PowerPlantSupply object. */
void PowerPlantSupply::addToSupply(PowerPlant *pp) {
	int value = (*pp).getValue();
	if (value <= 10) {
		market.push_back(*pp);
	}
	else if (value == 13) {
		supply[0] = *pp;
	}
	else {
		supply.push_back(*pp);
	}
}

/* Moves the last PowerPlant card of the supply to the market. Does not yet sort cards by number. */
void PowerPlantSupply::addToMarket() {
	PowerPlant pp = supply.back();
	supply.pop_back();
	market.push_back(pp);
}

/* Shuffles the supply. */
void PowerPlantSupply::shuffleSupply() {
	srand(unsigned(std::time(0)));
	random_shuffle(supply.begin()+1, supply.end());
}

/* Sells a PowerPlant to a certain Player for the price determined by bidding. */
bool PowerPlantSupply::sell(int index, Player *p, int price) {
	bool enoughMoney = p->removeMoney(price);
	if (!enoughMoney) {
		cout << "You don't have enough money for this transaction." << endl;
		return false;
	}
	p->addPlant(market[index]);
	market.erase(market.begin() + index);
	addToMarket();
}

/* Prints out the information of all the PowerPlants on the market. */
void PowerPlantSupply::printPlantSupply() {
	/*cout << "\n========== SUPPLY ==========" << endl;
	int count = 1;
	vector<PowerPlant>::iterator it;
	for (it = this->supply.begin(); it < this->supply.end(); it++) {
		cout << count << ". ";
		it->printPowerPlant();
		count++;
	}*/

	int count = 1;
	vector<PowerPlant>::iterator it;
	cout << "\n========== MARKET ==========" << endl;
	for (it = this->market.begin(); it < this->market.end(); it++) {
		cout << count << ". ";
		it->printPowerPlant();
		count++;
	}
}

/*********** LOAD/SAVE METHODS **********/

void PowerPlantSupply::savePPSContents(ofstream& ofs) {
	size_t supplySize = supply.size();
	ofs.write((char *)&supplySize, sizeof(supplySize));
	size_t marketSize = market.size();
	ofs.write((char *)&marketSize, sizeof(marketSize));

	vector<PowerPlant>::iterator it;
	for (it = supply.begin(); it < supply.end(); it++) {
		it->savePowerPlant(ofs);
	}
	for (it = market.begin(); it < market.end(); it++) {
		it->savePowerPlant(ofs);
	}
}

void PowerPlantSupply::loadPPSContents(ifstream& ifs) {
	size_t supplySize, marketSize;
	ifs.read((char *)&supplySize, sizeof(supplySize));
	ifs.read((char *)&marketSize, sizeof(marketSize));

	PowerPlant p = PowerPlant();
	for (int i = 0; i < supplySize; i++) {
		p.loadPowerPlant(ifs);
		supply.push_back(p);
	}
	for (int i = 0; i < marketSize; i++) {
		p.loadPowerPlant(ifs);
		market.push_back(p);
	}
}