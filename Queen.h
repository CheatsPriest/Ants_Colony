#pragma once
#include "Ant.h"
class Queen : public Ant
{
public:
	Queen(int x, int y, int z);
protected:
	void createNewAnt();

	int costToBorn;
	float speed;
	float coefOfQueen;

};

