#pragma once

class Maggot {
public:

	int clan;
	int release_timer;
	float hp;
	int pos_x;
	int pos_y;

	Maggot(int _clan, int _release_timer, int px, int py) {
		clan = _clan;
		pos_x = px;
		pos_y = py;
		release_timer = _release_timer;
		hp = 5.f;
	}

};