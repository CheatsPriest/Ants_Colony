#pragma once

#include "Ant.h"

class Colony {
public:

	int clan;
	
	int base_x, base_y, base_z;
	
	int scouts_courage;
	int delta_stock;


	int base_radius;

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
	
	Colony(int _clan, int x, int y, int z) {
		clan = _clan;

		base_x = x;
		base_y = y;
		base_z = z;

		base_radius = 50;
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

		//флаги
		needNewFoodStock = false;
		needNewMatStock = false;
		needNewAphidStock = false;
		needNewMaggotStock = false;

		

	}

};