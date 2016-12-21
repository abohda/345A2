/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef PLAYER_H
#define PLAYER_H

#include "House.h"
#include "Fuel.h"
#include "PowerPlant.h"
#include <vector>

#define NUM_PLAYERS 6

class Player {
private:
	string name;
	string colour;
	int turn;
	int money;

	vector<Fuel> fuel;
	vector<PowerPlant> plants;
	vector<City> cities;
	vector<House> houses;
public:
	Player();
	Player(string name);
	Player(string name, string colour);
	Player(string name, string colour, int money);

	void setName(string name);
	void setColour(string colour);
	void setTurn(int turn);
	void setAmountOfMoney(int amount);
	void setFuel(vector<Fuel> fuel);
	void setPowerPlants(vector<PowerPlant> plants);
	void setCities(vector<City> cities);
	void setHouses(vector<House> houses);

	string getName();
	string getColour();
	int getTurn();
	int getAmountOfMoney();
	vector<Fuel> getFuel();
	vector<PowerPlant> getPowerPlants();
	vector<City> getCities();
	vector<House> getHouses();
	int getCityCount();
	int getHouseCount();

	int getHousesPowered();
	int getMaxPlantNumber();

	void addFuel(Fuel f);
	void addFuel(int index, int amount);
	bool removeFuel(Fuel f);
	void addPlant(PowerPlant p);
	void addMoney(int amount);
	bool removeMoney(int amount);

	void printPlayer();
	void printFuel();
	void printPlants();
	void printCities();

	void savePlayer(ofstream& ofs);
	void loadPlayer(ifstream& ifs);
};

#endif