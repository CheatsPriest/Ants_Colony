#include "Stockpile.h"
#include "InfoSpace.h"

//ћуравей пытаетс€ положить на €чейку — Ћјƒј предмет или муравь€ и возвращает true если все успешно
bool Stockpile::TryToPut(Ant* curAnt, map<unsigned int, Entity*>* entityList) {
	int x, y;
	x = curAnt->pos_x - pos_x;
	y = curAnt->pos_y - pos_y;
	if (x<0 or y<0 or x>=size_x or y>=size_y or stuff[x][y]!=0) return false;

	stuff[x][y] = curAnt->Put();
	unsigned int carry_id = stuff[x][y];
	Entity* curCarried = (*entityList)[carry_id];

	if (curCarried->getType() == Entities::ANT) {
		Ant* carriedAnt = (Ant*)(curCarried->getPtr());
		
		carriedAnt->CopyPosition(curAnt);
		
		
	}
	else if (curCarried->getType() == Entities::FOOD) {
		Food* carriedFood = (Food*)(curCarried->getPtr());
		carriedFood->CopyPosition(curAnt);

		
	}

	
	
	return true;

}