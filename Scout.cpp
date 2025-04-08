#include "Scout.h"

Scout::Scout(int x, int y, int z, int clan) : Ant(x, y, z, 1, 90, 7, 0.1, 130,  clan), costToBorn(20), speed(2), coefOfScout(0.3)
{
	attack = max_HP * coefOfScout;
}

void Scout::lookFood()
{
}

void Scout::lookEnemies()
{
}
