/*	Written by Anastasiya Bohdanova, ID#40017040 */

#include "GameEngine.h"
#include <iostream>
#include <fstream>

/* A replacement for the SummaryCard class because having an entire class to represent this information felt really excessive. */
const int payments[21] = {
	10, 22, 33, 44, 54, 64, 73,
	82, 90, 98, 105, 112, 118, 124,
	129, 134, 138, 142, 145, 148, 150
};

/*********** METHODS DEMONSTRATING THE CAPACITIES OF THE OBSERVER PATTERN **********/

void testPattern() {
	m = new Map;
	mv = new MapView;

	m->attach(mv);

	bool loop = true;
	while (loop) {
		cout << "\nMain menu:" << endl;
		cout << "1. Add a city" << endl;
		cout << "2. Remove a city" << endl;
		cout << "3. Update a connection cost between 2 cities" << endl;
		cout << "4. Add a player" << endl;
		cout << "5. Add a house to the map" << endl;
		cout << "6. Print all cities' information" << endl;
		cout << "7. Exit" << endl;

		cout << "Choose an option between 1 and 7: ";
		int choice;
		cin >> choice;

		while (!cin || choice < 1 || choice > 7) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid choice. Please try again: ";
			cin >> choice;
		}

		switch (choice) {
		case 1:
			addCity();
			break;
		case 2:
			removeCity();
			break;
		case 3:
			updateConnection();
			break;
		case 4:
			addPlayer();
			break;
		case 5:
			addHouse();
			break;
		case 6:
			/* calls MapView::displayMap() */
			mv->displayMap();
			break;
		case 7:
			cout << "Exiting..." << endl;
			loop = false;
			break;
		}
	}

	delete m;
	delete mv;
}

void addCity() {
	string answer;

	while (true) {
		cout << "\nEnter a city name to add to the map: ";
		string cityName;
		cin >> cityName;

		cout << "\nEnter an area number: ";
		int area;
		cin >> area;
		
		/* calls Map::addCity() */
		m->addCity(cityName, area);

		cout << "\nAdd another city? (y/n) ";
		cin >> answer;

		while (answer != "y" && answer != "n") {
			cout << "Invalid answer. Please type y or n: ";
			cin >> answer;
		}

		if (answer == "n") {
			break;
		}
	}

	//m->printForDebug();
}

void removeCity() {
	string answer;

	while (true) {
		cout << "\nEnter a city name to remove from the map: ";
		string cityName;
		cin >> cityName;

		/* calls Map::removeCity() */
		m->removeCity(cityName);

		cout << "\nRemove another city? (y/n) ";
		cin >> answer;

		while (answer != "y" && answer != "n") {
			cout << "Invalid answer. Please type y or n: ";
			cin >> answer;
		}

		if (answer == "n") {
			break;
		}
	}

	//m->printForDebug();
}

void updateConnection() {
	string answer;

	while (true) {
		cout << "\nEnter first city name: ";
		string cityName1;
		cin >> cityName1;

		cout << "\nEnter second city name: ";
		string cityName2;
		cin >> cityName2;

		cout << "\nEnter connection cost: ";
		int cost;
		cin >> cost;

		while (!cin) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Please enter an integer value: ";
			cin >> cost;
		}

		/* calls Map::updateConnection() */
		m->updateConnection(cityName1, cityName2, cost);

		cout << "\nUpdate another connection? (y/n) ";
		cin >> answer;

		while (answer != "y" && answer != "n") {
			cout << "Invalid answer. Please type y or n: ";
			cin >> answer;
		}

		if (answer == "n") {
			break;
		}
	}

	//m->printForDebug();
}

void addPlayer() {
	string answer;

	while (true) {
		
		if (players.size() == 6) {
			cout << "The max number of players has been reached." << endl;
			return;
		}

		cout << "\nEnter a player name: ";
		string name;
		cin >> name;

		cout << "\nEnter a colour for " << name << ": ";
		string colour;
		cin >> colour;

		Player p = Player(name, colour, 50);
		players.push_back(p);

		cout << "\nAdd another player? (y/n) ";
		cin >> answer;

		while (answer != "y" && answer != "n") {
			cout << "Invalid answer. Please type y or n: ";
			cin >> answer;
		}

		if (answer == "n") {
			break;
		}
	}

	//printPlayers();
}

void addHouse() {
	if (players[0].getName() == "") {
		cout << "Please add a player before adding a house to the map." << endl;
		return;
	}

	if (m->getCities().empty()) {
		cout << "Please add a city before adding a house to the map." << endl;
		return;
	}

	string answer;

	while (true) {
		cout << "\nEnter player's name: ";

		bool validName = false;
		int playerIndex;
		while (!validName) {
			string name;
			cin >> name;

			for (playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++) {
				if (players[playerIndex].getName() == name) {
					validName = true;
					break;
				}
			}

			if (playerIndex == NUM_PLAYERS) {
				cout << "Invalid player name. Please try again: ";
			}
		}
		
		cout << "\nEnter a city: ";

		bool validCity = false;
		int cityIndex;
		while (!validCity) {
			string cityName;
			cin >> cityName;

			for (cityIndex = 0; cityIndex < m->getCities().size(); cityIndex++) {
				if (m->getCities()[cityIndex].getName() == cityName) {
					validCity = true;
					break;
				}
			}

			if (cityIndex == m->getCities().size()) {
				cout << "Invalid city name. Please try again: ";
			}
		}

		/* calls Map::addHouse() with city's index and player object */
		m->addHouse(cityIndex, &players[playerIndex]);

		cout << "\nAdd another house? (y/n) ";
		cin >> answer;

		while (answer != "y" && answer != "n") {
			cout << "Invalid answer. Please type y or n: ";
			cin >> answer;
		}

		if (answer == "n") {
			break;
		}
	}
}

void printPlayers() {
	for (int i = 0; i < players.size(); i++) {
		if (players[i].getName() == "") continue;
		cout << players[i].getName() << endl;
	}
}

/*********** METHODS ALLOWING GAMEPLAY **********/

void gameplay() {
	bool loaded = load();

	/* If no map was loaded from file, we need to build the Fuel and PowerPlant markets and instantiate some Players. */
	if (!loaded) {
		m = new Map(true);

		buildPowerPlantMarket();
		buildFuelMarket();

		addPlayer();
	}

	mv = new MapView;

	m->attach(mv);

	/* Allows for a limited number of turns to be played. */
	for (int i = 0; i < 1; i++) {
		playATurn();
	}

	save();

	delete m;
	delete mv;
}

void buildPowerPlantMarket() {
	pps.addToSupply(&PowerPlant("oil", "", 3, 2, 1));
	pps.addToSupply(&PowerPlant("coal", "", 4, 3, 2));
	pps.addToSupply(&PowerPlant("coal", "oil", 5, 2, 1));
	pps.addToSupply(&PowerPlant("garbage", "", 6, 1, 1));
	pps.addToSupply(&PowerPlant("oil", "", 7, 3, 2));
	pps.addToSupply(&PowerPlant("coal", "", 8, 3, 2));
	pps.addToSupply(&PowerPlant("oil", "", 9, 1, 1));
	pps.addToSupply(&PowerPlant("coal", "", 10, 2, 2));
	pps.addToSupply(&PowerPlant("uranium", "", 11, 1, 2));
	pps.addToSupply(&PowerPlant("coal", "oil", 12, 2, 2));
	pps.addToSupply(&PowerPlant("air", "", 13, 0, 1));
	pps.addToSupply(&PowerPlant("garbage", "", 14, 2, 2));
	pps.addToSupply(&PowerPlant("coal", "", 15, 2, 3));
	pps.addToSupply(&PowerPlant("oil", "", 16, 2, 3));
	pps.addToSupply(&PowerPlant("uranium", "", 17, 1, 2));
	pps.addToSupply(&PowerPlant("air", "", 18, 0, 2));
	pps.addToSupply(&PowerPlant("garbage", "", 19, 2, 3));
	pps.addToSupply(&PowerPlant("coal", "", 20, 3, 5));
	pps.addToSupply(&PowerPlant("coal", "oil", 21, 2, 4));
	pps.addToSupply(&PowerPlant("air", "", 22, 0, 2));
	pps.addToSupply(&PowerPlant("uranium", "", 23, 1, 3));
	pps.addToSupply(&PowerPlant("garbage", "", 24, 2, 4));
	pps.addToSupply(&PowerPlant("coal", "", 25, 2, 5));
	pps.addToSupply(&PowerPlant("oil", "", 26, 2, 5));
	pps.addToSupply(&PowerPlant("air", "", 27, 0, 3));
	pps.addToSupply(&PowerPlant("uranium", "", 28, 1, 4));
	pps.addToSupply(&PowerPlant("coal", "oil", 29, 1, 4));
	pps.addToSupply(&PowerPlant("garbage", "", 30, 3, 6));
	pps.addToSupply(&PowerPlant("coal", "", 31, 3, 6));
	pps.addToSupply(&PowerPlant("oil", "", 32, 2, 6));
	pps.addToSupply(&PowerPlant("air", "", 33, 0, 4));
	pps.addToSupply(&PowerPlant("uranium", "", 34, 1, 5));
	pps.addToSupply(&PowerPlant("oil", "", 35, 1, 5));
	pps.addToSupply(&PowerPlant("coal", "", 36, 3, 7));
	pps.addToSupply(&PowerPlant("air", "", 37, 0, 4));
	pps.addToSupply(&PowerPlant("garbage", "", 38, 3, 7));
	pps.addToSupply(&PowerPlant("uranium", "", 39, 1, 6));
	pps.addToSupply(&PowerPlant("oil", "", 40, 2, 6));
	pps.addToSupply(&PowerPlant("coal", "", 42, 3, 6));
	pps.addToSupply(&PowerPlant("air", "", 44, 0, 5));
	pps.addToSupply(&PowerPlant("coal", "oil", 46, 3, 7));
	pps.addToSupply(&PowerPlant("electricity", "", 50, 0, 6));

	pps.shuffleSupply();

	//pps.printPlantSupply();
}

void buildFuelMarket() {
	fs.addToSupply(&Fuel("coal", 0));
	fs.addToSupply(&Fuel("oil", 6));
	fs.addToSupply(&Fuel("garbage", 18));
	fs.addToSupply(&Fuel("uranium", 10));

	fs.addToMarket(&Fuel("coal", 24));
	fs.addToMarket(&Fuel("oil", 18));
	fs.addToMarket(&Fuel("garbage", 6));
	fs.addToMarket(&Fuel("uranium", 2));

	//fs.printFuelSupply();
}

/* Allows players to play one complete turn. */
void playATurn() {
	determineTurnOrder();
	buyPlants();
	buyFuel();
	placeHouses();
	payPlayers();
}

/* Determines player turn order for this turn. */
void determineTurnOrder() {
	/*
	If turn = 0 for any one player, this means that gameplay has not yet begun.
	Turn order is then determined for the first time.
	*/
	if (players[0].getTurn() == 0) {
		for (int i = 0; i < players.size(); i++) {
			players[i].setTurn((rand() % 10000) + 1);
		}
		sortPlayersByTurn(0);
	}
	else {
		sortPlayersByCities(0);
		/* FIX NEEDED: do a secondary sort by highest plant number. */
	}
}

/* FIX NEEDED: combine the 3 sort methods into 1. */

/* Recursively sorts the elements of the players array by turn order. Highest turn number goes first. */
void sortPlayersByTurn(int startingAt) {
	if (startingAt == players.size()) {
		return;
	}
	else {
		int maxIndex = 0;
		for (int i = startingAt; i < players.size(); i++) {
			if (players[i].getTurn() > players[maxIndex].getTurn()) {
				maxIndex = i;
			}
		}
		Player temp = players[maxIndex];
		players[maxIndex] = players[startingAt];
		players[startingAt] = temp;
		sortPlayersByTurn(startingAt + 1);
	}
}

/* Recursively sorts the elements of the players array by turn order. Lowest number of cities goes first. */
void sortPlayersByCities(int startingAt) {
	if (startingAt == players.size()) {
		return;
	}
	else {
		int minIndex = 0;
		for (int i = startingAt; i < players.size(); i++) {
			if (players[i].getCities().size() < players[minIndex].getCities().size()) {
				minIndex = i;
			}
		}
		Player temp = players[minIndex];
		players[minIndex] = players[startingAt];
		players[startingAt] = temp;
		sortPlayersByTurn(startingAt + 1);
	}
}

/* Recursively sorts the elements of the players array by turn order. Lowest max PowerPlant number goes first. Not currently used. */
void sortPlayersByPlant(int startingAt) {
	if (startingAt == players.size()) {
		return;
	}
	else {
		int minIndex = 0;
		for (int i = startingAt; i < players.size(); i++) {
			if (players[i].getMaxPlantNumber() < players[minIndex].getMaxPlantNumber()) {
				minIndex = i;
			}
		}
		Player temp = players[minIndex];
		players[minIndex] = players[startingAt];
		players[startingAt] = temp;
		sortPlayersByTurn(startingAt + 1);
	}
}

/*
Allows each player to buy a plant.
FIX NEEDED: allow players to opt out.
FIX NEEDED: make it so that if the player who initially chose the plant loses the bidding,
they have the option to choose another plant.
*/
void buyPlants() {
	for (int i = 0; i < players.size(); i++) {
		cout << "\n" << players[i].getName() << "'s turn to choose a plant!" << endl;
		pps.printPlantSupply();

		int plantNum = 0;
		cout << "Please enter the number (1-4) of the power plant you would like to buy: ";
		cin >> plantNum;

		while (!cin || plantNum < 1 || plantNum > 4) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid plant number. Please select a number between 1 and 4: ";
			cin >> plantNum;
		}

		int lastBid = pps.getMarketPlantAt(plantNum - 1)->getValue();
		int bidAmount = lastBid;

		int playerNum = i;
		while (true) {
			playerNum = (playerNum + 1) % players.size();
			cout << "Does " << players[playerNum].getName() << " want to bid? (y/n) ";
			string answer;
			cin >> answer;

			while (answer != "y" && answer != "n") {
				cout << "\nInvalid answer. Please type y or n: ";
				cin >> answer;
			}

			if (answer == "n") {
				break;
			}

			cout << "Enter bid amount: ";
			cin >> bidAmount;

			while (bidAmount <= lastBid) {
				cout << "Bid amount too low. Please enter a higher amount: ";
				cin >> bidAmount;
			}

		}

		playerNum = (playerNum + 1) % players.size();
		bool sold = pps.sell(plantNum - 1, &players[playerNum], bidAmount);

		if (sold) {
			cout << players[playerNum].getName() << " bought the plant." << endl;
		}
		else {
			cout << "An error occurred. " << players[playerNum].getName() << " was unable to buy the plant." << endl;
		}
	}
	printAllPlayers();
}

/*
Allows each player to buy fuel.
FIX NEEDED: allow players to opt out.
FIX NEEDED: make it so that if the player's choice of fuel to buy doesn't work out (e.g.
they don't have enough money for the transaction, they have a chance to modify their choice.
*/
void buyFuel() {
	for (int i = 0; i < players.size(); i++) {
		cout << "\n" << players[i].getName() << "'s turn to buy resources!" << endl;
		fs.printFuelSupply();

		cout << "Enter a resource type (coal, oil, garbage, uranium): ";
		string resourceType;
		cin >> resourceType;

		while (resourceType != "coal" && resourceType != "oil" && resourceType != "garbage" && resourceType != "uranium") {
			cout << "Invalid resource type. Please try again: ";
			cin >> resourceType;
		}

		int resourceIndex = 0;
		if (resourceType == "oil") resourceIndex = 1;
		else if (resourceType == "garbage") resourceIndex = 2;
		else if (resourceType == "uranium") resourceIndex = 3;

		cout << "Enter an amount of " << resourceType << " to buy: ";
		int resourceAmount;
		cin >> resourceAmount;

		while (resourceAmount > ((fs.getMarket())[resourceIndex]).getQuantity()) {
			cout << "Amount too high. Please enter a lower amount: ";
			cin >> resourceAmount;
		}

		bool sold = fs.sell(resourceIndex, resourceAmount, &players[i]);

		if (sold) {
			cout << players[i].getName() << " bought " << resourceAmount << " units of " << resourceType << "." << endl;
		}
		else {
			cout << "An error occurred. " << players[i].getName() << " was unable to buy the plant." << endl;
		}
	}
	printAllPlayers();
}

/*
Allows each player to place a house somewhere on the map.
FIX NEEDED: allow players to opt out.
FIX NEEDED: make it so that connection costs are incorporated into the price.
*/
void placeHouses() {
	for (int i = 0; i < players.size(); i++) {
		cout << "\n" << players[i].getName() << "'s turn to place a house!" << endl;
		
		mv->displayMap();

		bool available = false;
		int index = -1;
		string cityName;
		cout << "Enter a city to place a house in: ";

		while (!available) {
			index = -1;
			cin >> cityName;

			/*
			To check if the city name they entered is valid, we loop through the cities array and compare the user's input to
			cities that exist on the map. If the variable i goes out of range here, this means that the city name the user entered
			is not on the map.
			Note: case sensitive. All city names are capitalized.
			*/
			while (index == -1) {
				index = m->findCityIndex(cityName);
				if (index == -1) {
					cout << "Invalid city. Please try again: ";
					cin >> cityName;
				}
			}

			available = !(m->isFull(index));

			if (available) {
				break;
			}

			cout << cityName << " has no more room for additional houses. Please choose a different city: ";
			/* FIX NEEDED: need to check if all cities have a house placed. */
		}

		/* Place the house on the map. */
		m->addHouse(index, &players[i]);
		/* Remove cost of building one house */
		/* FIX NEEDED: increment cost based on count */
		players[i].removeMoney(10);

	}
}

/*
Pays Player according to the number of houses they can power.
FIX NEEDED: bug when not enough fuel.
*/
void payPlayers() {
	for (int i = 0; i < players.size(); i++) {
		int housesPowered = players[i].getHousesPowered();
		int payment = payments[housesPowered];
		/* FIX NEEDED: remove the appropriate amount of fuel from the Player's reserves & replace it in the market. */
		players[i].addMoney(payment);
	}
	printAllPlayers();
}

void printAllPlayers() {
	for (int i = 0; i < players.size(); i++) {
		players[i].printPlayer();
	}
}

/*********** SAVE & LOAD METHODS **********/

/* Saves the current state of Map to a binary file. */
bool save() {
	cout << "\nSaving map..." << endl;

	/* An output file stream is created. */
	ofstream ofs;
	ofs.open("map.dat", ios::out | ios::binary);

	if (!ofs.is_open()) {
		cerr << "Output file could not be opened." << endl;
		return false;
	}

	m->saveMap(ofs);
	
	int numPlayers = players.size();
	ofs.write((char *)&numPlayers, sizeof(int));
	for (int i = 0; i < numPlayers; i++) {
		players[i].savePlayer(ofs);
	}

	fs.saveFSContents(ofs);
	pps.savePPSContents(ofs);

	ofs.close();

}

/* Loads a map from file. */
bool load() {
	cout << "Loading map..." << endl;

	/* An input file stream is created. */
	ifstream ifs;
	ifs.open("map.dat", ios::in | ios::binary);

	/* Check if a map has been saved. If not, call buildMap to build a map from scratch. */
	if (ifs.peek() == ifstream::traits_type::eof()) {
		cout << "No saved file exists." << endl;
		return false;
	}

	m = new Map;

	m->loadMap(ifs);

	int numPlayers = 0;
	ifs.read((char *)&numPlayers, sizeof(int));
	players.resize(numPlayers);
	for (int i = 0; i < numPlayers; i++) {
		players[i].loadPlayer(ifs);
	}

	fs.loadFSContents(ifs);
	pps.loadPPSContents(ifs);

	ifs.close();
	return true;

}

int main() {

	/* comment out ln 713 to test only gameplay */
	testPattern();
	/* comment out ln 715 to evaluate the implementation of the observer pattern */
	//gameplay();

	return 0;
}