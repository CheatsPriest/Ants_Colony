#pragma once

const int levels = 1;
const int size_x = 250;
const int size_y = 250;
const int max_unit_per_cell_cap = 1;

class Cell {
public:
	bool isFree;
	unsigned int IDs[max_unit_per_cell_cap];
	Cell() { isFree = true; IDs[0] = 0; }
	//Удаляет и возвращает ID существа
	unsigned int CutEntity(int ind);
	void DeleteEntity(int ind);
};