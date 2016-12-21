/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef HOUSE_H
#define HOUSE_H

#include <string>

#include "City.h"

#define MAX_HOUSES 22

using namespace std;

class House {
private:
	string colour;
	City location;
public:
	House();
	House(string colour);
	House(string colour, City location);

	void setColour(string colour);
	void setLocation(City c);

	string getColour();
	City getLocation();

	void saveHouse(ofstream& ofs);
	void loadHouse(ifstream& ifs);
};

#endif