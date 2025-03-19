#include "Cell.h"

unsigned int Cell::CutEntity(int ind) {
	unsigned int buf= IDs[ind];
	IDs[ind] = 0;
	return buf;
}
void Cell::DeleteEntity(int ind) {
	IDs[ind] = 0;
	
}