#include "Soldier.h"


Soldier::Soldier() : Ant(), costToBorn(50), speed(1), coefOfSoldier(0.4)
{
	Ant(3, 200, 3, 0.1, 80);
	attack = max_HP * coefOfSoldier;
}

void Soldier::moveToPosition()
{
}

void Soldier::patrol()
{
}

void Soldier::attackTheEnemy()
{
}
