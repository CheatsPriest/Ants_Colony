#pragma once
#include "walls.h"

const int levels = 1;
const int size_x = 450;
const int size_y = 450;
const int max_unit_per_cell_cap = 1;

class Cell {
public:
	Wall* cWall;
	unsigned int IDs[max_unit_per_cell_cap];
	Cell() { cWall = 0; IDs[0] = 0; }
	//Удаляет и возвращает ID существа
	unsigned int CutEntity(int ind);
	void DeleteEntity(int ind);
	void CreateWall(float _max_hp, int _clan);
	void DeleteWall();
};