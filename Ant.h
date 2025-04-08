#pragma once
#include <iostream>
using namespace std;
#include <vector>


class Ant
{
public:
	Ant() {};
	Ant(int x, int y, int z, int type, float max_HP, int smell_Rad, float defense, float max_Saturation, int clan);
	void info() {
		cout << "I AM A SURGEON\n";
	}
	bool isAlive();
	void Eat(int id_food_in_entity);
	bool Take(unsigned int taked_id);
	unsigned int Put();
	void CopyPosition(Ant* source);
	void GivePosition(Ant* input);
	

	float HP;
	float max_HP;
	int action = 0;

	int pos_x;
	int pos_y;
	int pos_z;
	int dest;
	int source;

	unsigned int stashid;

	int clan;
	int smell_Rad;
	int paction;
	pair<int, int> aim = {pos_x,pos_y};
	pair<int, int> paim = { pos_x,pos_y };
	pair<int, int> nearest_En = { pos_x,pos_y };
	pair<int, int> nearest_Fd = { pos_x,pos_y };
	pair<int, int> nearest_Mat = { this->pos_x,this->pos_y };
	int ground_Lvl;
	float saturation;
	float max_Saturation;
	float attack;
	float defense;
	int type;

	unsigned int inventary;
	
};

