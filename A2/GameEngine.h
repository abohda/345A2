/*	Written by Anastasiya Bohdanova, ID#40017040 */

#ifndef DRIVER_H
#define DRIVER_H

#include "Map.h"
#include "MapView.h"
#include "PowerPlantSupply.h"
#include "FuelSupply.h"
#include <iostream>

Map *m;
MapView *mv;

vector<Player> players;

PowerPlantSupply pps;
FuelSupply fs;

void testPattern();
void addCity();
void removeCity();
void updateConnection();
void addPlayer();
void addHouse();
void printPlayers();

void gameplay();
void buildPowerPlantMarket();
void buildFuelMarket();
void playATurn();
void determineTurnOrder();
void sortPlayersByTurn(int startingAt);
void sortPlayersByCities(int startingAt);
void sortPlayersByPlant(int startingAt);
void buyPlants();
void buyFuel();
void placeHouses();
void payPlayers();
void printAllPlayers();

bool load();
bool save();

int main();

#endif