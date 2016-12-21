/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "MapView.h"

/*********** CITYINFO CLASS ***********/

	/*********** CONSTRUCTORS **********/

	MapView::CityInfo::CityInfo() {
		this->area = 0;
		this->houseCount = 0;
		associatedPlayers.resize(0);
		connections.resize(0);
	}

	MapView::CityInfo::CityInfo(City* city) {
		this->city = *city;
		this->area = city->getArea();
		this->houseCount = city->getHouseCount();
		associatedPlayers.resize(0);
		connections.resize(0);
	}

	/*********** SETTERS **********/

	void MapView::CityInfo::setAssociatedPlayers(vector<Player*> associatedPlayers) {
		this->associatedPlayers = associatedPlayers;
	}

	void MapView::CityInfo::setConnections(vector<int> connections) {
		this->connections = connections;
	}

	void MapView::CityInfo::addPlayer(Player* player) {
		this->associatedPlayers.push_back(player);
	}

	/*********** GETTERS **********/

	int MapView::CityInfo::getArea() {
		return area;
	}

	int MapView::CityInfo::getHouseCount() {
		return houseCount;
	}

	vector<Player*> MapView::CityInfo::getAssociatedPlayers() {
		return associatedPlayers;
	}

	vector<int> MapView::CityInfo::getConnections() {
		return connections;
	}

	string MapView::CityInfo::getCityName() {
		return this->city.getName();
	}

	/*********** OTHER METHODS **********/

	void MapView::CityInfo::addConnection(int cost) {
		connections.push_back(cost);
	}

	void MapView::CityInfo::updateConnection(int index, int cost) {
		connections[index] = cost;
	}
	
	void MapView::CityInfo::removeConnectionColumn(int index) {
		connections.erase(connections.begin() + index);
	}


	void MapView::CityInfo::printAssociatedPlayers() {
		cout << "Players: ";
		for (vector<Player*>::iterator it = associatedPlayers.begin(); it < associatedPlayers.end(); it++) {
			cout << (*it)->getName();
			if (it != associatedPlayers.end() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}

/*********** MAPVIEW CLASS ***********/

	/*********** CONSTRUCTOR **********/

	MapView::MapView() {
		allCities.resize(0);
	}

	/*********** GETTER **********/

	vector<MapView::CityInfo> MapView::getAllCities() {
		return allCities;
	}

	/*********** UPDATE METHODS **********/

	void MapView::resizeAllCities(int size) {
		allCities.resize(size);
	}
	
	void MapView::add(City* city, vector<int> connections) {
		int currentSize = allCities.size();
		for (int i = 0; i < currentSize; i++) {
			/* add connection column */
			allCities[i].addConnection(connections[i]);
		}

		CityInfo c = CityInfo(city);

		/* add connection row */
		c.setConnections(connections);

		/* push new CityInfo object */
		this->allCities.push_back(c);
	}

	void MapView::remove(int index) {
		/* removes the CityInfo object */
		allCities.erase(allCities.begin() + index);
	
		/* removes the connection from remaining CityInfo objects */
		for (int i = 0; i < allCities.size(); i++) {
			allCities[i].removeConnectionColumn(index);
		}
	}

	void MapView::update(int index, City* city, vector<int> connections, Player* player) {
		/* calls update() with the index, the city object and the connection vector */
		update(index, city, connections);
		/* adds the player */
		allCities[index].addPlayer(player);
	}

	void MapView::update(int index, City* city, vector<int> connections) {
		int currentSize = allCities.size() - 1;
		for (int i = 0; i < currentSize; i++) {
			/* calls CityInfo::updateConnection() with the appropriate index and connection value */
			allCities[i].updateConnection(index, connections[i]);
		}

		/* mirrors the city object that was passed */
		this->allCities[index] = city;
		/* sets connection vector */
		this->allCities[index].setConnections(connections);
	}

	void MapView::displayMap() {
		for (vector<CityInfo>::iterator it = allCities.begin(); it < allCities.end(); it++) {
			cout << "\n===== " << it->getCityName() << " =====" << endl;
			cout << "Area: " << it->getArea() << endl;
			cout << "Number of houses: " << it->getHouseCount() << endl;
			it->printAssociatedPlayers();
			printConnections(&(*it));
		}
	}

	void MapView::printConnections(CityInfo* c) {
		cout << "Connections: " << endl;
		for (int i = 0; i < c->getConnections().size(); i++) {
			if (c->getConnections()[i] != 0) {
				cout << "\t" << allCities[i].getCityName() << ": " << c->getConnections()[i] << endl;
			}
		}
	}