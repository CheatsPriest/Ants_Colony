#pragma once

class Wall {
public:

	//int pos_x;
	//int pos_y;
	//int pos_z;
	float hp;
	float max_hp;

	int clan;

	Wall(float _max_hp, int _clan) {
		max_hp = _max_hp;
		hp = max_hp;
		clan = _clan;
	}

};