#pragma once

#include "Entity.h"

class Stockpile {
public:
	int pos_x;
	int pos_y;
	int pos_z;
	int size_x;
	int size_y;
	int food_collected;
	vector<vector<Entity*>> stuff;
	Stockpile(int x, int y, int z, int wide, int hight) {
		pos_x = x;
		pos_y = y;
		pos_z = z;
		size_x = wide;
		size_y = hight;
		food_collected = 0;
		stuff.resize(size_y);
		for (int i = 0; i < size_y; i++) {
			stuff[i].resize(size_x);
			for (int j = 0; j < size_x; j++) {
				
				stuff[i][j] = 0;
			}
		}
	}

	bool TryToPut(Ant* ant);

};