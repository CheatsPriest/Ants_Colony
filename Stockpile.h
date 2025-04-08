#pragma once

#include "Entity.h"

enum Stockpiles {
	FOOD_STOCK = 0,
	MATERIAL_STOCK = 1, 
};

class Stockpile {
public:
	int pos_x;
	int pos_y;
	int pos_z;

	int clan;

	bool needWalled;

	int size_x;
	int size_y;
	int type;//0 - еда, 1 - стройматериалы, 2 - 
	int food_collected;
	unsigned int id;
	vector<vector<unsigned int>> stuff;
	
	Stockpile(int x, int y, int z, int wide, int hight, int cur_type, unsigned int cr_id, int cr_clan) {

		needWalled = false;

		pos_x = x;
		pos_y = y;
		pos_z = z;

		clan = cr_clan;

		size_x = wide;
		size_y = hight;
		type = cur_type;
		food_collected = -1;
		id = cr_id;
		stuff.resize(size_y);
		for (int i = 0; i < size_y; i++) {
			stuff[i].resize(size_x);
			for (int j = 0; j < size_x; j++) {
				
				stuff[i][j] = 0;
			}
		}
	}

	bool TryToPut(Ant* ant, map<unsigned int, Entity*>* entityList, pair<int,int>where);
	unsigned int AntIslEating(Ant* curAnt, map<unsigned int, Entity*>* entityList);
	unsigned int PickUp(Ant* curAnt, map<unsigned int, Entity*>* entityList);
};