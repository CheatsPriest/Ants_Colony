#pragma once

#include "Ant.h"

class Colony {
public:

	int clan;
	
	int base_x, base_y, base_z;
	
	int scouts_courage;

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

		//������������ �����
		scouts_courage = 5;

		//�����
		needNewFoodStock = false;
		needNewMatStock = false;
		needNewAphidStock = false;
		needNewMaggotStock = false;

	}

};