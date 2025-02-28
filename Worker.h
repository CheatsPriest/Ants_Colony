#pragma once
#include "Ant.h"
class Worker : public Ant
{
public:
	Worker();
protected:
	void haul();

	int costToBorn;
	float speed;
	float coefOfWorker;
};

