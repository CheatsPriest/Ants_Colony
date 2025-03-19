#pragma once
#include <iostream>
using namespace std;
#include <vector>

class Ant
{
public:
	
	Ant(int x, int y, int z, int type, float max_HP, int smell_Rad, float defense, float max_Saturation);
	void info() {
		cout << "I AM ANT\n";
	}
	bool isAlive();
	void Eat();
	void Move(int pos_X, int pos_Y, int smell_Rad);

	float HP;
	float max_HP;
	int action;

	int pos_x;
	int pos_y;
	int pos_z;

	int level;//Пока что 1
	int smell_Rad;
	vector<pair<int, int>> aim;
	vector<pair<int, int>> nearest_En;
	int ground_Lvl;
	float saturation;
	float max_Saturation;
	float attack;
	float defense;
	int type;


	
};

