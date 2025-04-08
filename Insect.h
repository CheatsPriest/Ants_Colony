#ifndef HHH
#define HHH
#include "Entity.h"
enum InsectTypes {
	APHID = 1
};
class Insect
{
public:
	static pair<int, pair<int,int>> nearlest;
	InsectTypes type;
	int agressive;
	int pos_x;
	int pos_y;
	int pos_z;
	float max_hp;
	float hp;
	int id;
	float saturation;
	float max_saturation;
	float attack;
	float deffense;
	unsigned int aim_id;
	unsigned int store;
	pair<int, int> aim_pos;
	bool isTriggered;
	pair<int, int> stockPos;
	pair<int, int> stockSize;
	void setAimId(unsigned int id) {
		aim_id = id;
	}
	Insect(InsectTypes type, int x, int y, int z) {
		this->id = id;
		this->type = type;
		pos_x = x;
		pos_y = y;
		pos_z = z;
		isTriggered = false;
	}
	void info() {
		cout << "I am INSECT" << "\n";
	}
	bool isIndoors(int x, int y) {
		return( stockPos.first < x) && (x < stockPos.first + stockSize.first)
			&& (stockPos.second < y) &&( y < stockPos.second + stockSize.second);
	
	}

};


#endif