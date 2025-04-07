#pragma once
#include "Entity.h"
#include "InfoSpace.h"
enum InsectTypes {
	APHID = 1
};
class Insect
{
public:
	int id;
	InsectTypes type;
	int agressive;
	int pos_x;
	int pos_y;
	int pos_z;
	float max_hp;
	float hp;
	float saturation;
	float max_saturation;
	float attack;
	float deffense;
	Insect(InsectTypes type, int x, int y, int z) {
		this->id = id;
		this->type = type;
		pos_x = x;
		pos_y = y;
		pos_z = z;
	}
};

