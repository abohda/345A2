/*	Written by Anastasiya Bohdanova, ID#40017040 */

/* 
	FIX NEEDED: add support for the game phases.
	In phase 3, all 8 plants can be bought.
*/

#include "FuelSupply.h"

/*********** CONSTRUCTORS **********/

FuelSupply::FuelSupply() {
	market.resize(0);
}

/*********** GETTERS **********/

vector<Fuel> FuelSupply::getSupply() {
	return supply;
}

vector<Fuel> FuelSupply::getMarket() {
	return market;
}

/*********** OTHER METHODS **********/

/* Used only in the construction of the FuelSupply object. */
void FuelSupply::addToSupply(Fuel *f) {
	supply.push_back(*f);
}

/* Used in the initial construction of the market. */
void FuelSupply::addToMarket(Fuel *f) {
	market.push_back(*f);
}

/* Used to move fuel between the supply and the market. */
void FuelSupply::addToMarket(string type, int quantity) {
	int index;
	if (type == "coal") index = 0;
	else if (type == "oil") index = 1;
	else if (type == "garbage") index = 2;
	else index = 0;

	supply[index].removeFuel(quantity);
	market[index].addFuel(quantity);
}

/* Sells a certain amount of fuel to a Player p. */
bool FuelSupply::sell(int index, int amount, Player *p) {
	int count = amount;
	int completeBoxes, remainder, boxIndex;
	int price = 0;
	int amountAvailable = market[index].getQuantity();

	if (index < 3) {
		completeBoxes = amountAvailable / 3;
		remainder = amountAvailable % 3;
		boxIndex = 8 - completeBoxes;

		while (remainder > 0 && count > 0) {
			price += boxIndex;
			remainder--;
			count--;
		}

		while (count > 0) {
			boxIndex++;

			int i = 3;
			while (i > 0) {
				price += boxIndex;
				i--;
				count--;
			}
		}	
	}

	bool sold = p->removeMoney(price);
	if (sold) {
		market[index].removeFuel(amount);
		p->addFuel(index, amount);
	}

	return sold;
}

/* Prints out the market. */
void FuelSupply::printFuelSupply() {
	/*cout << "\n========== SUPPLY ==========" << endl;
	vector<Fuel>::iterator it;
	for (it = this->supply.begin(); it < this->supply.end(); it++) {
		it->toString();
	}*/

	cout << "\n========== MARKET ==========" << endl;
	vector<Fuel>::iterator it;
	for (it = this->market.begin(); it < this->market.end(); it++) {
		cout << endl;
		it->printFuel();
		if (it->getType() == "uranium") {
			int price = 16;
			for (int i = it->getQuantity(); i > 0; i--) {
				if (price >= 10 && price%2 == 1) {
					price--;
				}
				cout << "1 uranium at " << price << " Elektro" << endl;
				price--;
			}
		}
		else {
			int price = 8;
			for (int i = it->getQuantity(); i > 0; i-=3) {
				if (i >= 3) {
					cout << "3 ";
				}
				else {
					cout << i << " ";
				}
				cout << it->getType() << " at " << price << " Elektro" << endl;
				price--;
			}
		}
	}
}

/*********** LOAD/SAVE METHODS **********/

void FuelSupply::saveFSContents(ofstream& ofs) {
	size_t supplySize = supply.size();
	ofs.write((char *)&supplySize, sizeof(supplySize));
	size_t marketSize = market.size();
	ofs.write((char *)&marketSize, sizeof(marketSize));

	vector<Fuel>::iterator it;
	for (it = supply.begin(); it < supply.end(); it++) {
		it->saveFuel(ofs);
	}
	for (it = market.begin(); it < market.end(); it++) {
		it->saveFuel(ofs);
	}
}

void FuelSupply::loadFSContents(ifstream& ifs) {
	size_t supplySize, marketSize;
	ifs.read((char *)&supplySize, sizeof(supplySize));
	ifs.read((char *)&marketSize, sizeof(marketSize));

	Fuel f = Fuel();
	for (int i = 0; i < supplySize; i++) {
		f.loadFuel(ifs);
		supply.push_back(f);
	}
	for (int i = 0; i < marketSize; i++) {
		f.loadFuel(ifs);
		market.push_back(f);
	}
}