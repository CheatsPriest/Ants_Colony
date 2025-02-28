#pragma once
#include "Ant.h"
class Scout : public Ant
{
public:
	Scout();
protected:
	void lookFood();
	void lookEnemies();

	int costToBorn;
	float speed;
	float coefOfScout;
};

