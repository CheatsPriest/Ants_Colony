#pragma once
#include <iostream>
#include "Ant.h"

class Food
{
public:
	int entity_id;
	int type;
	int pos_x;
	int pos_y;
	int pos_z;
	float food_value;
	int weight;
	Food(int x, int y, int z, int type, float food_value, int weight) {
		this->pos_x = x;
		this->pos_y = y;
		this->pos_z = z;
		this->type = type;
		this->food_value = food_value;
		this->weight = weight;
	}
	void info() {
		std::cout << "I AM FOOD\n";
	}

	void CopyPosition(Ant* hauler);

};

