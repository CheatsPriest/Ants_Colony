#pragma once

#include "Ant.h"

class Colony {
public:

	int clan;
	
	int base_x, base_y, base_z;
	
	int scouts_courage;
	int delta_stock;
	int chanceOfIncreasingRadius;

	int base_radius;
	int spreading_radius;

	void NullEverything();

	bool needNewFoodStock,
		needNewMatStock,
		needNewAphidStock,
		needNewMaggotStock;

	long long curFoodAmount,
		curMaterialAmount,
		curAphidAmount,
		curMaggotAmount;

	unsigned int numWorker,
		numScouts,
		numSoldier,
		numNurses;

	//other stats
	unsigned int died;

	bool momyClosestStock;
	unsigned int closestStockToQueen;

	Ant* Queen;

	float red;
	float green;
	float blue;
	
	Colony(int _clan, int x, int y, int z) {
		clan = _clan;

		base_x = x;
		base_y = y;
		base_z = z;

		base_radius = 70;
		spreading_radius = 10;

		numWorker = 0;
		numScouts = 0;
		numSoldier = 0;
		numNurses = 0;
		curFoodAmount = 0;
		curMaterialAmount = 0;
		curAphidAmount = 0;
		
		died = 0;

		//динамические статы
		scouts_courage = 2;
		delta_stock = 15;
		chanceOfIncreasingRadius = 35; 

		//флаги
		needNewFoodStock = false;
		needNewMatStock = false;
		needNewAphidStock = false;
		needNewMaggotStock = false;

		red = (float)(rand() % 100) / 100;
		green = (float)(rand() % 100) / 100;
		blue = (float)(rand() % 100) / 100;


	}

};