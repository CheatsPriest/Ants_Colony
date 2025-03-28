#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "Food.h"
#include "InfoSpace.h"
class Ant
{
public:
	Ant() {};
	Ant(int x, int y, int z, int type, float max_HP, int smell_Rad, float defense, float max_Saturation);
	void info() {
		cout << "I AM A SURGEON\n";
	}
	void eat(int);
	bool isAlive();
	void Eat();
	

	float HP;
	float max_HP;
	int action = 0;

	int pos_x;
	int pos_y;
	int pos_z;

	int level;//Пока что 1
	int smell_Rad;
	pair<int, int> aim = {pos_x,pos_y};
	pair<int, int> nearest_En = { pos_x,pos_y };
	pair<int, int> nearest_Fd;
	int ground_Lvl;
	float saturation;
	float max_Saturation;
	float attack;
	float defense;
	int type;

	
};

