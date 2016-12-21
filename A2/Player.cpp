/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "Player.h"

/*********** CONSTRUCTORS **********/

Player::Player() {
	this->name = "";
	this->colour = "";
	this->turn = 0;
	this->money = 0;

	fuel.resize(0);
	plants.resize(0);
	cities.resize(0);
	houses.resize(0);
}

Player::Player(string name) {
	this->name = name;
	this->colour = "";
	this->turn = 0;
	this->money = 0;

	fuel.resize(0);
	plants.resize(0);
	cities.resize(0);
	houses.resize(0);
}

Player::Player(string name, string colour) {
	this->name = name;
	this->colour = colour;
	this->turn = 0;
	this->money = 0;

	fuel.resize(0);
	plants.resize(0);
	cities.resize(0);
	houses.resize(0);
}

Player::Player(string name, string colour, int money) {
	this->name = name;
	this->colour = colour;
	this->turn = 0;
	this->money = money;

	fuel.resize(0);
	plants.resize(0);
	cities.resize(0);
	houses.resize(0);
}

/*********** SETTERS **********/

void Player::setName(string name) {
	this->name = name;
}

void Player::setColour(string colour) {
	this->colour = colour;
}

void Player::setTurn(int turn) {
	this->turn = turn;
}

void Player::setAmountOfMoney(int m) {
	this->money = m;
}

void Player::setFuel(vector<Fuel> fuel) {
	this->fuel = fuel;
}

void Player::setPowerPlants(vector<PowerPlant> plants) {
	this->plants = plants;
}

void Player::setCities(vector<City> cities) {
	this->cities = cities;
}

void Player::setHouses(vector<House> houses) {
	this->houses = houses;
}

/*********** GETTERS **********/

string Player::getName() {
	return name;
}

string Player::getColour() {
	return colour;
}

int Player::getTurn() {
	return turn;
}

int Player::getAmountOfMoney() {
	return money;
}

vector<Fuel> Player::getFuel() {
	return fuel;
}

vector<PowerPlant> Player::getPowerPlants() {
	return plants;
}

vector<City> Player::getCities() {
	return cities;
}

vector<House> Player::getHouses() {
	return houses;
}

int Player::getCityCount() {
	return cities.size();
}

int Player::getHouseCount() {
	return houses.size();
}

/*********** OTHER METHODS **********/

/*
FIX NEEDED: allow players to choose how many houses to power & which power plants to use;
don't default to the maximum powerable
*/
int Player::getHousesPowered() {
	int powered = 0;
	vector<Fuel> fuelRequired;

	vector<PowerPlant>::iterator it;
	for (it = plants.begin(); it < plants.end(); it++) {
		Fuel f = Fuel(it->getType1(), it->getAmount());
		bool removed = removeFuel(f);
		if (removed) {
			powered += it->getNumberHouses();
		}
		else {
			f = Fuel(it->getType2(), it->getAmount());
			removed = removeFuel(f);
			if (removed) {
				powered += it->getNumberHouses();
			}
		}
	}

	return powered;
}

int Player::getMaxPlantNumber() {
	int max = 100;						// arbitrarily large number
	vector<PowerPlant>::iterator it;
	for (it = plants.begin(); it < plants.end(); it++) {
		if (it->getValue() > max) {
			max = it->getValue();
		}
	}

	return max;
}

/*
For the next two methods, recall that a Fuel vector holds at most 4 Fuel objects, one for every fuel
type. This is unlike PowerPlant vectors, which hold as many PowerPlant objects as there are plants.
This may be something to change later on, but that's how it is for now.
*/

/* Increases fuel quantity at the appropriate index. */
void Player::addFuel(Fuel f) {
	if (fuel.size() < 4) {
		fuel.resize(4);
	}
	string type = f.getType();
	int quantity = f.getQuantity();
	int index = 0;
	if (type == "oil") index = 1;
	else if (type == "garbage") index = 2;
	else if (type == "uranium") index = 3;
	fuel[index].addFuel(quantity);
}

void Player::addFuel(int index, int amount) {
	if (fuel.size() < 4) {
		fuel.resize(4);
	}
	fuel[index].addFuel(amount);
}

/* Decreases fuel quantity at the appropriate index. */
bool Player::removeFuel(Fuel f) {
	string type = f.getType();
	int quantity = f.getQuantity();
	int index = 0;
	if (type == "oil") index = 1;
	else if (type == "garbage") index = 2;
	else if (type == "uranium") index = 3;
	return (fuel[index].removeFuel(quantity));
}

/* Adds PowerPlant objects directly to the player's PowerPlant vector. */
void Player::addPlant(PowerPlant p) {
	plants.push_back(p);
}

void Player::addMoney(int amount) {
	this->money += amount;
}

/*
Returns false if amount to remove exceeds the amount of money the player has.
Otherwise removes the amount and returns true.
*/
bool Player::removeMoney(int amount) {
	if (amount > this->money) {
		cout << name << " doesn't have enough money for this transaction." << endl;
		return false;
	}
	this->money -= amount;
	return true;
}

/* A method to print out a player's information. */
void Player::printPlayer() {
	cout << "\nPlayer name: " << name << endl;
	cout << "Colour: " << colour << endl;
	cout << "Money: " << money << " Elektro" << endl;
	printFuel();
	printPlants();
	printCities();
}

/* A helper method for printPlayer() to print out information about the Fuel vector. */
void Player::printFuel() {
	cout << "Fuel: ";
	if (fuel.empty()) cout << "none" << endl;
	else {
		cout << "\t" << fuel[0].getQuantity() << " coal" << endl;
		cout << "\t" << fuel[1].getQuantity() << " oil" << endl;
		cout << "\t" << fuel[2].getQuantity() << " garbage" << endl;
		cout << "\t" << fuel[3].getQuantity() << " uranium" << endl;
	}
}

/* A helper method for printPlayer() to print out information about the PowerPlant vector. */
void Player::printPlants() {
	cout << "Power plants: ";
	if (plants.empty()) cout << "none" << endl;
	else {
		vector<PowerPlant>::iterator it;
		for (it = this->plants.begin(); it < this->plants.end(); it++) {
			if (it->getType2() == "") {
				cout << "\n\t\t" << it->getType1() << " plant worth " << it->getValue() << " Elektro, uses " << it->getAmount() << " units of fuel to power " << it->getNumberHouses() << " houses" << endl;
			}
			else {
				cout << "\n\t\t" << it->getType1() << "/" << it->getType2() << " plant worth " << it->getValue() << " Elektro, uses " << it->getAmount() << " units of fuel to power " << it->getNumberHouses() << " houses" << endl;
			}
		}
	}
}

/* A helper method for printPlayer() to print out information about the City vector. */
void Player::printCities() {
	cout << "Cities: ";
	if (cities.empty()) cout << "none" << endl;
	else {
		vector<City>::iterator it;
		for (it = this->cities.begin(); it < this->cities.end(); it++) {
			cout << it->getName();
			if (it < this->cities.end() - 1) {
				cout << ", ";
			}
		}
	}
}

/*********** LOAD/SAVE METHODS **********/

void Player::savePlayer(ofstream& ofs) {
	size_t len = name.size();
	ofs.write((char *)&len, sizeof(size_t));
	ofs.write(name.c_str(), name.length());

	len = colour.size();
	ofs.write((char *)&len, sizeof(size_t));
	ofs.write(colour.c_str(), colour.length());

	ofs.write((char *)(&turn), sizeof(int));
	ofs.write((char *)(&money), sizeof(int));

	size_t size = fuel.size();
	ofs.write((char *)&size, sizeof(int));
	vector<Fuel>::iterator itFuel;
	for (itFuel = fuel.begin(); itFuel < fuel.end(); itFuel++) {
		itFuel->saveFuel(ofs);
	}

	size = plants.size();
	ofs.write((char *)&size, sizeof(int));
	vector<PowerPlant>::iterator itPlants;
	for (itPlants = plants.begin(); itPlants < plants.end(); itPlants++) {
		itPlants->savePowerPlant(ofs);
	}

	size = cities.size();
	ofs.write((char *)&size, sizeof(int));
	vector<City>::iterator itCity;
	for (itCity = cities.begin(); itCity < cities.end(); itCity++) {
		itCity->saveCity(ofs);
	}

	size = houses.size();
	ofs.write((char *)&size, sizeof(int));
	vector<House>::iterator itHouse;
	for (itHouse = houses.begin(); itHouse < houses.end(); itHouse++) {
		itHouse->saveHouse(ofs);
	}
}

void Player::loadPlayer(ifstream& ifs) {
	size_t len;
	ifs.read((char *)&len, sizeof(size_t));
	char* temp = new char[len + 1];
	ifs.read(temp, len);
	temp[len] = '\0';
	this->name = temp;

	ifs.read((char *)&len, sizeof(size_t));
	temp = new char[len + 1];
	ifs.read(temp, len);
	temp[len] = '\0';
	this->colour = temp;
	delete[] temp;

	ifs.read((char *)(&turn), sizeof(int));
	ifs.read((char *)(&money), sizeof(int));
	
	size_t fuelSize, plantsSize, citiesSize, housesSize;

	ifs.read((char *)&fuelSize, sizeof(int));
	Fuel f = Fuel();
	for (int i = 0; i < fuelSize; i++) {
		f.loadFuel(ifs);
		fuel.push_back(f);
	}

	ifs.read((char *)&plantsSize, sizeof(int));
	PowerPlant p = PowerPlant();
	for (int i = 0; i < plantsSize; i++) {
		p.loadPowerPlant(ifs);
		plants.push_back(p);
	}

	ifs.read((char *)&citiesSize, sizeof(int));
	City c = City();
	for (int i = 0; i < citiesSize; i++) {
		c.loadCity(ifs);
		cities.push_back(c);
	}

	ifs.read((char *)&housesSize, sizeof(int));
	House h = House();
	for (int i = 0; i < housesSize; i++) {
		h.loadHouse(ifs);
		houses.push_back(h);
	}
}