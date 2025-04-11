#pragma once

#include "Ant.h"

class Colony {
public:

	int clan;
	Ant* Queen;
	
	Colony(int _clan) {
		clan = _clan;
	}

};