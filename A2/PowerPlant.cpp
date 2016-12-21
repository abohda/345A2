/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "PowerPlant.h"

/*********** CONSTRUCTORS **********/

PowerPlant::PowerPlant() {
	this->fuelType1 = "";
	this->fuelType2 = "";
	this->fuelAmount = 0;
	this->housesPowered = 0;
	this->value = 0;
}

PowerPlant::PowerPlant(string type1, string type2, int value, int amount, int houses) {
	this->fuelType1 = type1;
	this->fuelType2 = type2;
	this->fuelAmount = amount;
	this->housesPowered = houses;
	this->value = value;
}

/* Note: no setters are necessary since a power plant's information should not be changed once it's assigned. */

/*********** GETTERS **********/

string PowerPlant::getType1() {
	return fuelType1;
}

string PowerPlant::getType2() {
	return fuelType2;
}

int PowerPlant::getAmount() {
	return fuelAmount;
}

int PowerPlant::getNumberHouses() {
	return housesPowered;
}

int PowerPlant::getValue() {
	return value;
}

/*********** OTHER **********/

void PowerPlant::printPowerPlant() {
	if (fuelType2 == "") {
		cout << fuelType1 << " type power plant, costs " << value << " Elektro" << endl;
		if (fuelAmount == 0) {
			cout << "powers " << housesPowered << " house(s)\n" << endl;
		}
		else {
			cout << "uses " << fuelAmount << " " << fuelType1 << " to power " << housesPowered << " house(s)\n" << endl;
		}
	}
	else {
		cout << fuelType1 << "/" << fuelType2 << " type power plant, costs " << value << " Elektro" << endl;
		cout << "uses " << fuelAmount << " " << fuelType1 << " or " << fuelType2 << " to power " << housesPowered << " house(s)\n" << endl;
	}
}

/*********** LOAD/SAVE METHODS **********/

void PowerPlant::savePowerPlant(ofstream& ofs) {
	size_t len = fuelType1.size();
	ofs.write((char *)&len, sizeof(size_t));
	ofs.write(fuelType1.c_str(), fuelType1.length());

	len = fuelType2.size();
	ofs.write((char *)&len, sizeof(size_t));
	ofs.write(fuelType2.c_str(), fuelType2.length());

	ofs.write((char *)(&fuelAmount), sizeof(fuelAmount));
	ofs.write((char *)(&housesPowered), sizeof(housesPowered));
	ofs.write((char *)(&value), sizeof(value));
}

void PowerPlant::loadPowerPlant(ifstream& ifs) {
	this->fuelType1 = loadFuelType(ifs);
	this->fuelType2 = loadFuelType(ifs);

	ifs.read((char *)(&fuelAmount), sizeof(fuelAmount));
	ifs.read((char *)(&housesPowered), sizeof(housesPowered));
	ifs.read((char *)(&value), sizeof(value));
}

string PowerPlant::loadFuelType(ifstream& ifs) {
	size_t len;
	ifs.read((char *)&len, sizeof(size_t));
	char* temp = new char[len + 1];
	ifs.read(temp, len);
	temp[len] = '\0';
	string fuelType = temp;
	delete[] temp;
	return fuelType;
}