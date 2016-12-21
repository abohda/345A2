/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "City.h"
#include "Player.h"
#include <vector>

class MapView {
private:
	class CityInfo {
		City city;
		int area;
		int houseCount;
		vector<Player*> associatedPlayers;
		vector<int> connections;
	public:
		CityInfo();
		CityInfo(City* city);

		void setAssociatedPlayers(vector<Player*> associatedPlayers);
		void setConnections(vector<int> connections);
		void addPlayer(Player* player);

		int getArea();
		int getHouseCount();
		vector<Player*> getAssociatedPlayers();
		vector<int> getConnections();
		string getCityName();

		void addConnection(int cost);
		void updateConnection(int index, int cost);
		void removeConnectionColumn(int index);

		void printAssociatedPlayers();
	};

	vector<CityInfo> allCities;
public:
	MapView();

	vector<CityInfo> getAllCities();

	void resizeAllCities(int size);

	void add(City* city, vector<int> connections);
	void remove(int index);
	void update(int index, City* city, vector<int> connections, Player* player);
	void update(int index, City* city, vector<int> connections);

	void displayMap();
	void printConnections(CityInfo* c);
};

#endif