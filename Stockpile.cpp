#include "Stockpile.h"
#include "InfoSpace.h"

//ћуравей пытаетс€ положить на €чейку — Ћјƒј предмет или муравь€ и возвращает true если все успешно
bool Stockpile::TryToPut(Ant* curAnt, map<unsigned int, Entity*>* entityList, pair<int, int> where) {
	if (food_collected == size_x * size_y) { return false; }
	int x, y;
	x = food_collected%size_x;
	y = food_collected/size_x;
	
	stuff[x][y] = curAnt->Put();
	unsigned int carry_id = stuff[x][y];
	Entity* curCarried = (*entityList)[carry_id];
	food_collected++;
	cout << 1;
	if (curCarried->getType() == Entities::ANT) {
		Ant* carriedAnt = (Ant*)(curCarried->getPtr());
		
		carriedAnt->pos_x = x+pos_x;
		carriedAnt->pos_y = y + pos_y;
		
	}
	else if (curCarried->getType() == Entities::FOOD) {
		Food* carriedFood = (Food*)(curCarried->getPtr());
		carriedFood->pos_x = x + pos_x;
		carriedFood->pos_y =y + pos_y;
		
	}

	
	
	return true;

}