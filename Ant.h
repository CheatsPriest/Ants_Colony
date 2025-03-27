#pragma once
#include <iostream>
using namespace std;
#include <vector>


class Ant
{
public:
	Ant() {};
	Ant(int x, int y, int z, int type, float max_HP, int smell_Rad, float defense, float max_Saturation);
	void info() {
		//cout << "I AM ANT\n";
	}
	bool isAlive();
	void Eat();
	

	float HP;
	float max_HP;
	int action;

	int pos_x;
	int pos_y;
	int pos_z;

	int level;//Пока что 1
	int smell_Rad;
	pair<int, int> aim = {pos_x,pos_y};
	pair<int, int> nearest_En = { pos_x,pos_y };
	pair<int, int> nearest_Fd = { 1000,1000 };
	int ground_Lvl;
	float saturation;
	float max_Saturation;
	float attack;
	float defense;
	int type;


	
};

