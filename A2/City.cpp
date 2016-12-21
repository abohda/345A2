/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "City.h"

/*********** CONSTRUCTORS **********/

City::City() {
	this->name = "";
	this->area = 0;
	houses = new string[HOUSES_SUPPORTED];
}

City::City(string name, int area) {
	this->name = name;
	this->area = area;
	houses = new string[HOUSES_SUPPORTED];
}

/*********** SETTERS **********/

void City::setName(string name) {
	this->name = name;
}

/*********** GETTERS **********/

string City::getName() {
	return this->name;
}

int City::getArea() {
	return this->area;
}

string* City::getHouses() {
	return this->houses;
}

int City::getHouseCount() {
	int count = 0;
	while (!houses[count].empty()) {
		count++;
	}
	return count;
}

bool City::isFull() {
	int count = getHouseCount();
	if (count == 3) {
		return true;
	}
	return false;
}

/*********** OTHER METHODS **********/

bool City::addHouse(string colour) {
	int freeIndex;
	for (freeIndex = 0; freeIndex < houses->size(); freeIndex++) {
		if (houses[freeIndex].empty()) {
			break;
		}
	}

	if (freeIndex == HOUSES_SUPPORTED) {
		cout << "There is no more room in " + this->name + " to build houses." << endl;
		return false;
	}

	houses[freeIndex] = colour;
	cout << "A " << colour << " house was successfully placed in " << this->name << "." << endl;
	return true;
}

void City::printCity() {
	cout << "========== " + this->name + " ==========" << endl;

	for (int i = 0; i < houses->size(); i++) {
		if (!houses[i].empty()) {
			cout << "House no." << (i + 1) << ": " + houses[i] << endl;
		}
		else {
			break;
		}
	}
}

/*********** LOAD/SAVE METHODS **********/

void City::saveCity(ofstream& ofs) {
	size_t len = name.size();
	ofs.write((char *)&len, sizeof(size_t));
	ofs.write(name.c_str(), name.length());
	
	for (int i = 0; i < HOUSES_SUPPORTED; i++) {
		len = houses[i].size();
		ofs.write((char *)&len, sizeof(size_t));
		ofs.write(houses[i].c_str(), houses[i].length());
	}
}

void City::loadCity(ifstream& ifs) {
	size_t len;

	ifs.read((char *)&len, sizeof(size_t));
	char* temp = new char[len + 1];
	ifs.read(temp, len);
	temp[len] = '\0';
	this->name = temp;

	for (int i = 0; i < HOUSES_SUPPORTED; i++) {
		ifs.read((char *)&len, sizeof(size_t));
		temp = new char[len + 1];
		ifs.read(temp, len);
		temp[len] = '\0';
		this->houses[i] = temp;
	}

	delete[] temp;
}