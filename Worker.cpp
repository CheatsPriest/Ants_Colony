#include "Worker.h"

Worker::Worker() : Ant(), costToBorn(30), speed(1), coefOfWorker(0.3)
{
	Ant(2, 100, 3, 0.1, 100);
	attack = max_HP * coefOfWorker;
}

void Worker::haul()
{
}
