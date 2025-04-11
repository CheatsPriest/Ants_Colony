#include "Nurse.h"

Nurse::Nurse(int x, int y, int z, int clan) : Ant(x, y, z, 4, 100, 3, 0.1, 150, clan), costToBorn(30), speed(1), coefOfWorker(0.3)
{
	attack = max_HP * coefOfWorker;
}


