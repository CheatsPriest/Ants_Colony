#include "Soldier.h"


Soldier::Soldier(int x, int y, int z) : Ant(x, y, z, 3, 200, 3, 0.1, 160), costToBorn(50), speed(1), coefOfSoldier(0.4)
{
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
