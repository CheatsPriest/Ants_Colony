#pragma once
#include "Ant.h"
class Scout : public Ant
{
public:
	Scout(int x, int y, int z);
protected:
	void lookFood();
	void lookEnemies();

	int costToBorn;
	float speed;
	float coefOfScout;
};

