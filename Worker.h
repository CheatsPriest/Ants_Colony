#pragma once
#include "Ant.h"
class Worker : public Ant
{
public:
	Worker(int x, int y, int z);
protected:
	void haul();

	int costToBorn;
	float speed;
	float coefOfWorker;
};

