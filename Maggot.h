#pragma once

class Maggot {
public:

	int clan;
	int release_timer;
	float hp;

	Maggot(int _clan, int _release_timer) {
		clan = _clan;
		release_timer = _release_timer;
		hp = 5.f;
	}

};