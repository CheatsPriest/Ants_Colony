#pragma once
#include "Ant.h"
class Soldier : public Ant
{
public:
	Soldier();
protected:
	void moveToPosition();
	void patrol();
	void attackTheEnemy();

	int costToBorn;
	float speed;
	float coefOfSoldier;
	
};

