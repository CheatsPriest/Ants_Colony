#pragma once
#include "Ant.h"
class Scout : public Ant
{
public:
	Scout(int x, int y, int z, int clan);
protected:
	void lookFood();
	void lookEnemies();

	int costToBorn;
	float speed;
	float coefOfScout;
};

