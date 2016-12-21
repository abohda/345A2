/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef CITY_H
#define CITY_H

#include <string>
#include <iostream>
#include <fstream>

#define HOUSES_SUPPORTED 3
#define NUM_CITIES 21

using namespace std;

class City {
private:
	string name;
	int area;
	string* houses;
public:
	City();
	City(string name, int area);

	void setName(string name);
	bool addHouse(string colour);

	string getName();
	int getArea();
	string* getHouses();
	int getHouseCount();
	bool isFull();

	void printCity();

	void saveCity(ofstream& ofs);
	void loadCity(ifstream& ifs);
};

#endif