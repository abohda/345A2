/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "MapView.h"

using namespace std;

class Map {
private:
	static const string cityNames[NUM_CITIES];
	static const vector<vector<int>> defaultAdjMatrix;

	vector<City> cities;
	vector<vector<int>> adjMatrix;

	vector<MapView*> observers;
public:
	Map();
	Map(bool buildDefault);

	vector<City> getCities();
	vector<vector<int>> getAdjMatrix();
	int findCityIndex(string cityName);
	bool isFull(int index);

	bool addCity(string cityName, int area);
	bool updateConnection(string city1, string city2, int cost);
	bool removeCity(string cityName);
	bool addHouse(int cityIndex, Player* player);

	void attach(MapView* observer);
	void detach(MapView* observer);
	
	void addNotify();
	void updateNotify(int index);
	void updateNotify(int index, Player* player);
	void removeNotify(int index);

	void printForDebug();

	void saveMap(ofstream& ofs); 
	void loadMap(ifstream& ifs);
};

#endif