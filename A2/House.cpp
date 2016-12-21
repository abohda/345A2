/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "House.h"

/*********** CONSTRUCTORS **********/

House::House() {
	this->colour = "";
}

House::House(string colour) {
	this->colour = colour;
}

House::House(string colour, City location) {
	this->colour = colour;
	this->location = location;
}

/*********** SETTERS **********/

void House::setColour(string colour) {
	this->colour = colour;
}

void House::setLocation(City c) {
	this->location = c;
}

/*********** GETTERS **********/

string House::getColour() {
	return colour;
}

City House::getLocation() {
	return location;
}

/*********** LOAD/SAVE METHODS **********/

void House::saveHouse(ofstream& ofs) {
	size_t len = colour.size();
	ofs.write((char *)&len, sizeof(size_t));
	ofs.write(colour.c_str(), colour.length());

	location.saveCity(ofs);
}

void House::loadHouse(ifstream& ifs) {
	size_t len;
	ifs.read((char *)&len, sizeof(size_t));
	char* temp = new char[len + 1];
	ifs.read(temp, len);
	temp[len] = '\0';
	this->colour = temp;
	delete[] temp;

	location.loadCity(ifs);
}