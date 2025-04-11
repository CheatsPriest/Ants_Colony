#pragma once


#include "Ant.h"
class Nurse : public Ant
{
public:
	Nurse(int x, int y, int z, int clan);
protected:

	int costToBorn;
	float speed;
	float coefOfWorker;
};

