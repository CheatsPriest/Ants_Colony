#include "Cell.h"

unsigned int Cell::CutEntity(int ind) {
	unsigned int buf= IDs[ind];
	IDs[ind] = 0;
	return buf;
}
void Cell::DeleteEntity(int ind) {
	IDs[ind] = 0;
	
}

void Cell::CreateWall(float _max_hp, int _clan) {

	Wall* curWall = new Wall(_max_hp, _clan);

	cWall = curWall;

}

void Cell::DeleteWall() {
	cWall = 0;
	delete cWall;

}