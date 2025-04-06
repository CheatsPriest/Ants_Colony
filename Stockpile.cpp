#include "Stockpile.h"
#include "InfoSpace.h"

//ћуравей пытаетс€ положить на €чейку — Ћјƒј предмет или муравь€ и возвращает true если все успешно
unsigned int Stockpile::AntIslEating(Ant* curAnt, map<unsigned int, Entity*>* entityList) {

	unsigned int food_ind;
	int x, y;
	x = food_collected % size_x;
	y = food_collected / size_x;
	if (food_collected == 0) {
		cout << "END";
	}
	if (x>=0 && y>=0 && y< size_y &&stuff[x][y] != 0 and food_collected>0) {
		Entity* targEnt = (*entityList)[stuff[x][y]];

		food_ind = stuff[x][y];

		if (targEnt->getType() == Entities::FOOD) {

			Food* curFood = (Food*)(targEnt->getPtr());
			float need = curAnt->max_Saturation - curAnt->saturation;
			float itog = min(need, curFood->food_value);
			curAnt->saturation += itog;
			curFood->food_value -= itog;

			if (curFood->food_value<=0 && food_collected > 0) {
				food_collected--;
				stuff[x][y] = 0;
				return food_ind;
			}

		}
	}
	else if(x>=0 and y>=0 and food_collected>0) {
		food_collected--;
	}
	return 0;

}
bool Stockpile::TryToPut(Ant* curAnt, map<unsigned int, Entity*>* entityList, pair<int, int> where) {
	if (food_collected == size_x * size_y) { return false; }
	int x, y;
	if (food_collected == -1) { food_collected++; }
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