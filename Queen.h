#pragma once
#include "Ant.h"
class Queen : public Ant
{
public:
	Queen();
protected:
	void createNewAnt();

	int costToBorn;
	float speed;
	float coefOfQueen;

};

