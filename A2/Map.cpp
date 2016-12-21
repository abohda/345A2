/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "Map.h"

const string Map::cityNames[NUM_CITIES] = {
	/* YELLOW */ "Gatineau", "MontTremblant", "Montreal", "LaTuque", "TroisRivieres", "Sherbrooke", "Quebec",
	/* RED */ "RapidesDesJoachims", "LeDomaine", "Timbrell", "RouynNoranda", "ValDOr", "LebelSurQuevillon", "Chibougamau",
	/* ORANGE */ "Chicoutimi", "ChuteDesPasses", "Labrieville", "Rimouski", "ManicCinq", "BaieComeau", "Matane"
};

const vector<vector<int>> Map::defaultAdjMatrix = {
	{ 0,3,4,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 3,0,3,6,5,0,0,0,6,8,0,0,0,0,0,0,0,0,0,0,0 },
	{ 4,3,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,6,0,0,4,0,4,0,0,7,0,0,0,12,7,0,0,0,0,0,0 },
	{ 0,5,4,4,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,4,0,3,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0 },
	{ 0,0,0,4,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },

	{ 6,0,0,0,0,0,0,0,5,0,10,9,0,0,0,0,0,0,0,0,0 },
	{ 6,6,0,0,0,0,0,5,0,7,0,6,0,0,0,0,0,0,0,0,0 },
	{ 0,8,0,7,0,0,0,0,7,0,0,9,9,11,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,10,0,0,0,4,7,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,9,6,9,4,0,6,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,9,7,6,0,10,0,0,0,0,0,0 },
	{ 0,0,0,12,0,0,0,0,0,11,0,0,10,0,12,8,0,0,0,0,0 },

	{ 0,0,0,7,0,0,5,0,0,0,0,0,0,12,0,9,7,8,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,8,9,0,8,0,9,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,8,0,5,7,4,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,5,0,0,4,4 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,7,0,0,7,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,7,0,3 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,3,0 }
};

/*********** CONSTRUCTORS **********/

Map::Map() {
	cities.resize(0);
	adjMatrix.resize(0);
	observers.resize(0);
}

Map::Map(bool buildDefault) {
	cities.resize(0);
	adjMatrix.resize(0);
	observers.resize(0);

	/* In this for loop, NUM_CITIES City objects are created and stored in the cities vector. */
	int area;
	for (int i = 0; i < NUM_CITIES; i++) {
		if (i < 7) area = 1;
		else if (i < 14) area = 2;
		else area = 3;
		cities.push_back(City(cityNames[i], area));
	}

	adjMatrix = defaultAdjMatrix;
}

/*********** GETTERS **********/

vector<City> Map::getCities() {
	return this->cities;
}

vector<vector<int>> Map::getAdjMatrix() {
	return this->adjMatrix;
}

/* Finds where in the cities array a particular city is located. */
int Map::findCityIndex(string cityName) {
	/*
	To check if the city name they entered is valid, we loop through the cities array and compare the user's input to
	cities that exist on the map. If the variable i goes out of range here, this means that the city name the user entered
	is not on the map.
	Note: case sensitive. All city names are capitalized.
	FIX NEEDED: remove case sensitivity
	*/
	int index = -1;
	for (int i = 0; i < NUM_CITIES; i++) {
		if (this->cities[i].getName() == cityName) {
			index = i;
			break;
		}
	}
	return index;
}

bool Map::isFull(int index) {
	return cities[index].isFull();
}

/*********** METHODS TO MODIFY THE MAP **********/

bool Map::addCity(string cityName, int area) {
	for (int i = 0; i < cities.size(); i++) {
		if (cities[i].getName() == cityName) {
			cout << cityName << " is already on the map." << endl;
			return false;
		}
	}
	City c = City(cityName, area);
	cities.push_back(c);

	/* set all connections for this city to 0 */
	int currentSize = adjMatrix.size();
	vector<int> connections(0);
	for (int i = 0; i < currentSize; i++) {
		adjMatrix[i].push_back(0);
		connections.push_back(0);
	}
	connections.push_back(0);
	adjMatrix.push_back(connections);

	cout << cityName << " was successfully added to the list of cities." << endl;

	/* calls appropriate notify method */
	addNotify();
	return true;
}

bool Map::updateConnection(string city1, string city2, int cost) {
	if (city1 == city2) {
		cout << "Connections must be between different cities." << endl;
		return false;
	}

	int city1Index = cities.size();
	int city2Index = cities.size();

	for (int i = 0; i < cities.size(); i++) {
		if (cities[i].getName() == city1) {
			city1Index = i;
		}
		if (cities[i].getName() == city2) {
			city2Index = i;
		}
	}

	if (city1Index == cities.size()) {
		cout << city1 << " is not in the list of cities. Add it to the list of cities before making a connection." << endl;
		return false;
	}
	if (city2Index == cities.size()) {
		cout << city2 << " is not in the list of cities. Add it to the list of cities before making a connection." << endl;
		return false;
	}

	if (city1Index > city2Index) {
		int temp = city1Index;
		city1Index = city2Index;
		city2Index = temp;
	}

	adjMatrix[city1Index][city2Index] = cost;
	adjMatrix[city2Index][city1Index] = cost;
	
	/* calls appropriate notify method on both cities' indexes */
	updateNotify(city1Index);
	updateNotify(city2Index);
	return true;
}

bool Map::removeCity(string cityName) {
	int initialSize = cities.size();

	int index;
	for (index = 0; index < cities.size(); index++) {
		if (cities[index].getName() == cityName) {
			cities.erase(cities.begin() + index);
			break;
		}
	}

	if (index == initialSize) {
		cout << cityName << " is not on the map." << endl;
		return false;
	}

	/* erase connection row */
	adjMatrix.erase(adjMatrix.begin() + index);

	/* erase connection column */
	if (adjMatrix.size() != 0) {
		int currentSize = adjMatrix[0].size() - 1;
		for (int i = 0; i < currentSize; i++) {
			adjMatrix[i].erase(adjMatrix[i].begin() + index);
		}
	}

	cout << cityName << " was successfully removed from the list of cities." << endl;

	/* calls appropriate notify method */
	removeNotify(index);
	return true;
}

bool Map::addHouse(int cityIndex, Player* player) {
	if (player->getHouseCount() == MAX_HOUSES) {
		cout << player->getName() << " has built the maximum number of houses." << endl;
		return false;
	}

	/* calls City::addHouse() with player's colour as parameter */
	bool success = cities[cityIndex].addHouse(player->getColour());

	if (!success) {
		return false;
	}

	/* calls appropriate notify method with city's index and player object */
	updateNotify(cityIndex, player);
	return true;
}

/*********** OBSERVER PATTERN METHODS **********/

void Map::attach(MapView* observer) {
	observers.push_back(observer);
	if (cities.size() > observer->getAllCities().size()) {
		for (int i = 0; i < cities.size(); i++) {
			observer->add(&cities[i], adjMatrix[i]);
		}
	}
}

void Map::detach(MapView* observer) {
	for (vector<MapView*>::iterator it = observers.begin(); it < observers.end(); it++) {
		if (&(*it) == &observer) {
			observers.erase(it);
		}
	}
}

void Map::addNotify() {
	for (vector<MapView*>::iterator it = observers.begin(); it < observers.end(); it++) {
		/* calls MapView::add() with the last city and connection vector that were added */
		(*it)->add(&cities.back(), adjMatrix.back());
	}
}

void Map::updateNotify(int index) {
	for (vector<MapView*>::iterator it = observers.begin(); it < observers.end(); it++) {
		/* calls MapView::update() with the index, the city object and the connection vector */
		(*it)->update(index, &cities[index], adjMatrix[index]);
	}
}

void Map::updateNotify(int index, Player* player) {
	for (vector<MapView*>::iterator it = observers.begin(); it < observers.end(); it++) {
		/* calls MapView::update() with the index, the city object, the connection vector and the player */
		(*it)->update(index, &cities[index], adjMatrix[index], player);
	}
}

void Map::removeNotify(int index) {
	for (vector<MapView*>::iterator it = observers.begin(); it < observers.end(); it++) {
		/* calls MapView::remove() with the appropriate index */
		(*it)->remove(index);
	}
}

void Map::printForDebug() {
	for (int i = 0; i < cities.size(); i++) {
		cout << cities[i].getName() << ": ";
		for (int j = 0; j < adjMatrix[i].size(); j++) {
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

/*********** LOAD/SAVE METHODS **********/

void Map::saveMap(ofstream& ofs) {
	for (int i = 0; i < NUM_CITIES; i++) {
		cities[i].saveCity(ofs);
	}
}

void Map::loadMap(ifstream& ifs) {
	adjMatrix = defaultAdjMatrix;
	cities.resize(NUM_CITIES);
	for (int i = 0; i < NUM_CITIES; i++) {
		cities[i].loadCity(ifs);
	}
}