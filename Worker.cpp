#include "Worker.h"

Worker::Worker(int x, int y, int z) : Ant(), costToBorn(30), speed(1), coefOfWorker(0.3)
{
	Ant(x, y, z, 2, 100, 3, 0.1, 100);
	attack = max_HP * coefOfWorker;
}

void Worker::haul()
{
}
