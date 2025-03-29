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
	vector<Entity*> stuff;
	Stockpile(int x, int y, int z, int wide, int hight) {
		pos_x = x;
		pos_y = y;
		pos_z = z;
		size_x = wide;
		size_y = hight;
		food_collected = 0;
		stuff.resize(0);
	}
};