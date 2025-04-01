#include "Stockpile.h"
#include "InfoSpace.h"

//ћуравей пытаетс€ положить на €чейку — Ћјƒј предмет или муравь€ и возвращает true если все успешно
bool Stockpile::TryToPut(Ant* curAnt, map<unsigned int, Entity*>* entityList, pair<int,int> where) {
	int x, y;
	x = where.first- pos_x;
	y = where.second - pos_y;
	if (x < 0 or y < 0 or x > size_x or y > size_y or stuff[x][y] != 0) x = (x) % size_x; y=y+(x);

	stuff[x][y] = curAnt->Put();
	unsigned int carry_id = stuff[x][y];
	Entity* curCarried = (*entityList)[carry_id];
	food_collected++;
	cout << 1;
	if (curCarried->getType() == Entities::ANT) {
		Ant* carriedAnt = (Ant*)(curCarried->getPtr());
		
		carriedAnt->pos_x = where.first;
		carriedAnt->pos_y = where.second;
		
	}
	else if (curCarried->getType() == Entities::FOOD) {
		Food* carriedFood = (Food*)(curCarried->getPtr());
		carriedFood->pos_x = where.first;
		carriedFood->pos_y = where.second;
		

		
	}

	
	
	return true;

}