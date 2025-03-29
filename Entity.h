#pragma once
#include <map>
#include "Ant.h"
#include "Food.h"
#include "Insect.h"

using namespace std;


enum Entities {
	ANT = 0,
	FOOD = 1,
	INSECT = 2
};
class Entity {
private:
	Entities type;
	void* ptr;

public:
	Entity(void* ptr, Entities type) {
		this->type = type;
		this->ptr = ptr;

	}
	Entities getType() {
		return type;
	}
	void* getPtr() {
		return this->ptr;
	}
	int pos_x;
	int pos_y;
	int pos_z;
};

