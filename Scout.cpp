#include "Scout.h"

Scout::Scout() : Ant(), costToBorn(20), speed(2), coefOfScout(0.3)
{
	Ant(1, 90, 7, 0.1, 50);
	attack = max_HP * coefOfScout;
}

void Scout::lookFood()
{
}

void Scout::lookEnemies()
{
}
