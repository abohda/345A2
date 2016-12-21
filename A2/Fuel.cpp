/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "Fuel.h"

/*********** CONSTRUCTORS **********/

Fuel::Fuel() {
	this->type = "";
	this->quantity = 0;
}

Fuel::Fuel(string type, int quantity) {
	this->type = type;
	this->quantity = quantity;
}

/*********** MUTATORS **********/

void Fuel::addFuel(int amount) {
	this->quantity += amount;
}

bool Fuel::removeFuel(int amount) {
	if (amount > this->quantity) {
		cout << "Not enough fuel to remove." << endl;
		return false;
	}
	this->quantity -= amount;
	return true;
}

/* Note: no setter is needed for fuel type, since this is a value that shouldn't be changed once a type is assigned. */

/*********** GETTERS **********/

string Fuel::getType() {
	return type;
}

int Fuel::getQuantity() {
	return quantity;
}

/*********** OTHER METHODS **********/

void Fuel::printFuel() {
	cout << quantity << " " << type << endl;
}

/*********** LOAD/SAVE METHODS **********/

void Fuel::saveFuel(ofstream& ofs) {
	size_t len = type.size();
	ofs.write((char *)&len, sizeof(size_t));
	ofs.write(type.c_str(), type.length());

	ofs.write((char *)(&quantity), sizeof(quantity));
}

void Fuel::loadFuel(ifstream& ifs) {
	size_t len;
	ifs.read((char *)&len, sizeof(size_t));
	char* temp = new char[len + 1];
	ifs.read(temp, len);
	temp[len] = '\0';
	this->type = temp;
	delete[] temp;

	ifs.read((char *)(&quantity), sizeof(quantity));
}