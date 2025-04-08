#pragma once
#include "Ant.h"
class Soldier : public Ant
{
public:
	Soldier(int x, int y, int z, int clan);
protected:
	void moveToPosition();
	void patrol();
	void attackTheEnemy();

	int costToBorn;
	float speed;
	float coefOfSoldier;
	
};

