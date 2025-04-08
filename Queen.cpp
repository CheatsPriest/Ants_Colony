#include "Queen.h"

Queen::Queen(int x, int y, int z, int clan) : Ant(x, y, z, 0, 1000, 0,1000, 0.1, clan), costToBorn(1000), speed(1), coefOfQueen(0.3)
{
	attack = max_HP * coefOfQueen;
}

void Queen::createNewAnt()
{
}
