#include "Stockpile.h"
#include "InfoSpace.h"


bool Stockpile::TryToPut(Ant* curAnt) {
	int x, y;
	x = curAnt->pos_x - pos_x;
	y = curAnt->pos_y - pos_y;
	if (x<0 or y<0 or x>size_x or y>size_y or stuff[x][y]!=0) return false;

	


}