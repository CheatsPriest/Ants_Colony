#pragma once
#include "walls.h"

const int levels = 1;
const int size_x = 2000;
const int size_y = 2000;
const int max_unit_per_cell_cap = 1;

class Cell {
public:
	Wall* cWall = nullptr;
	unsigned int IDs[max_unit_per_cell_cap];
	unsigned int stockID;
	Cell() { cWall = 0; IDs[0] = 0; }
	//Удаляет и возвращает ID существа
	unsigned int CutEntity(int ind);
	void DeleteEntity(int ind);
	void CreateWall(float _max_hp, int _clan);
	void DeleteWall();
};