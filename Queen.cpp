#include "Queen.h"

Queen::Queen() : Ant(), costToBorn(1000), speed(1), coefOfQueen(0.3)
{
	Ant(0, 1000, 0, 0.1, 1000);
	attack = max_HP * coefOfQueen;
}

void Queen::createNewAnt()
{
}
