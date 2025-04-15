#include "InfoSpace.h"
#include <algorithm>
#include "Insect.h"
#include <queue>
using namespace std;





bool InfoSpace::isValidCell(pair<int, int> newPos) {

	return !(newPos.first >= field_size_x || newPos.second >= field_size_y
		|| newPos.first < 0 || newPos.second < 0);
}
bool InfoSpace::isFreeCell(pair<int, int> newPos2) {
	return field->field[newPos2.first][newPos2.second][0].IDs[0] == 0;
}

void InfoSpace::moveToCeil(pair<int, int> newPos2, unsigned int id, Insect* curr) {
	if (field->field[newPos2.first][newPos2.second][0].cWall != 0 or abs(curr->pos_x-newPos2.first)>2 or abs(curr->pos_y - newPos2.second) > 2)return;
	field->field[curr->pos_x][curr->pos_y][0].IDs[0] = 0;	
	field->field[newPos2.first][newPos2.second][0].IDs[0] = id;
	curr->pos_x = newPos2.first;
	curr->pos_y = newPos2.second;
}

void InfoSpace::moveToCeilBackBase(pair<int, int> newPos2, unsigned int id, Insect* curr) {
	//if (field->field[newPos2.first][newPos2.second][0].cWall != 0 or abs(curr->pos_x - newPos2.first) > 2 or abs(curr->pos_y - newPos2.second) > 2)return;
	field->field[curr->pos_x][curr->pos_y][0].IDs[0] = 0;
	field->field[newPos2.first][newPos2.second][0].IDs[0] = id;
	curr->pos_x = newPos2.first;
	curr->pos_y = newPos2.second;
}
void InfoSpace::RandomMove(pair<int, int> newPos2, unsigned int id, Insect* insect) {


	pair<int, int> expectedPoint = newPos2;
	if (isValidCell(expectedPoint) && isFreeCell(expectedPoint) && insect->isIndoors(expectedPoint.first, expectedPoint.second, field)) {
		moveToCeil(expectedPoint, id, insect);
		return;
	}
	else {
		int k = 0;
		pair<int, int> p;
		while (k <= 10) {
			p.first = insect->pos_x + rand() % 3 - 1;
			p.second = insect->pos_y + rand() % 3 - 1;
			if (isValidCell(p) && isFreeCell(p) && insect->isIndoors(p.first, p.second, field)) {
				moveToCeil(p, id, insect);
				break;
			}
			k++;
		}
	}
}


pair<bool, Stockpile*> InfoSpace::IndoorsStockpile(pair<int, int> p) {
	for (int i = 1; i < free_stockpile_key; i++) {
		Stockpile* stock = stockpileList[i];
		if (p.first > stock->pos_x && p.first < stock->pos_x + stock->size_x
			&& p.second > stock->pos_y && p.second < stock->pos_y + stock->size_x) {
			return { true, stock };
		}
	}
	return { false, nullptr };
}

void InfoSpace::MoveLadybug(unsigned int id, Insect* insect) {
	
	//возвращение на базу какую нибудь
if (insect->goToBase) {
	if (pow(insect->aim_pos.first - insect->pos_x, 2) + pow(insect->aim_pos.second - insect->pos_y, 2) <= 200) {
		insect->goToBase = false;
		return;
	}

	pair<int, int> direct = { 0,0 };
	if (insect->pos_x < insect->aim_pos.first) {
		direct.first = 1;
	}
	else {
		direct.first = -1;
	}
	if (insect->pos_y < insect->aim_pos.second) {
		direct.second = 1;
	}
	else {
		direct.second = -1;
	}

	pair<int, int> expectedPoint = { insect->pos_x + direct.first, insect->pos_y + direct.second };

	if (isValidCell(expectedPoint) && isFreeCell(expectedPoint)) {
		moveToCeilBackBase(expectedPoint, id, insect);
		(expectedPoint, id, insect);
		return;
	}
	else {
		int k = 0;
		pair<int, int> p;
		while (k <= 10) {
			p.first = insect->pos_x + rand() % 3 - 1;
			p.second = insect->pos_y + rand() % 3 - 1;
			if (isValidCell(p) && isFreeCell(p)) {
				moveToCeilBackBase(p, id, insect);
				break;
			}
			k++;
		}
	}



	RandomMove(expectedPoint, id, insect);
	
	return;
}

//если оказались в зоне любого склада
pair<bool, Stockpile*> ps = IndoorsStockpile({ insect->pos_x, insect->pos_y });
bool detectedAphid = false;
Insect* aphid;
pair<int, int> detectedCoord = { 0, 0 };
if (ps.first) {
	if (ps.second->type == 0) {
		ps.second->PickUpWithoutAnt();
		insect->goToBase = true;
		insect->isTriggered = false;
		insect->updateBaseCoords(field_size_x, field_size_y);
		insect->aim_pos = insect->baseCoords;
		return;
	}
	else if (ps.second->type == 1) {
		ps.second->PickUpWithoutAnt();
		insect->goToBase = true;
		insect->isTriggered = false;
		insect->updateBaseCoords(field_size_x, field_size_y);
		insect->aim_pos = insect->baseCoords;
		return;
	}
	else if (ps.second->type == 2) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (j == i && j == 0) continue;
				unsigned int currEntityId = field->field[insect->pos_x + i][insect->pos_y + j][0].IDs[0];
				if (currEntityId != 0 && entityList[currEntityId]->getType() == Entities::INSECT
					&& (aphid = (Insect*)entityList[currEntityId]->getPtr())->type == InsectTypes::APHID) {
					detectedAphid= true;
					detectedCoord = { insect->pos_x + i, insect->pos_y + j };
					//нашли тлю на складе
				}
			}
		}
	}
	else if (ps.second->type == 3) {
		ps.second->PickUpWithoutAnt();
		insect->goToBase = true;
		insect->isTriggered = false;
		insect->updateBaseCoords(field_size_x, field_size_y);
		insect->aim_pos = insect->baseCoords;

		return;
	}
	
	if (detectedAphid) {
		unsigned int id_ = field->field[detectedCoord.first][detectedCoord.second][0].IDs[0];
		field->field[detectedCoord.first][detectedCoord.second][0].IDs[0] = 0;
		entityList.erase(id_);
		cout << "KILLED" << "\n";
		insect->goToBase = true;
		insect->isTriggered = false;
		insect->updateBaseCoords(field_size_x, field_size_y);
		insect->aim_pos = insect->baseCoords;

	} else {
		// ищем цель на складе
		RandomMove({ insect->pos_x, insect->pos_y }, id, insect);
	}
	return;
}


//если не на складе
if (!insect->isTriggered) {
		if (free_stockpile_key == 0) return;
		
		int targetId = rand() % (free_stockpile_key - 1) + 1;
		Stockpile* stockpile = stockpileList[targetId];
		insect->aim_id = targetId;
		insect->aim_pos = { stockpile->pos_x + stockpile->size_x / 2, stockpile->pos_y + stockpile->size_x / 2 };
		insect->isTriggered = true;
		
	}
	else if(insect->isTriggered){
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == j && j == 0) continue;
				if (!isValidCell({ insect->pos_x + i, insect->pos_y + j })) continue;
				if (field->field[insect->pos_x + i][insect->pos_y + j][0].cWall != 0) {
					insect->goToBase = true;
					insect->isTriggered = false;
					insect->aim_pos = insect->baseCoords;
					return;
				}
	
			}
		}

		pair<int, int> direct = { 0,0 };
		if (insect->pos_x < insect->aim_pos.first) {
			direct.first = 1;
		}
		else {
			direct.first = -1;
		}
		if (insect->pos_y < insect->aim_pos.second) {
			direct.second = 1;
		}
		else  {
			direct.second = -1;
		}
		RandomMove({ insect->pos_x + direct.first , insect->pos_y + direct.second}, id, insect);

	}
	
}

void InfoSpace::MoveAphid(unsigned int id, Insect* insect) {
	if (!insect->isTriggered) {

		if (insect->nearlest.first != 0 && (insect->isSlaveZone == insect->isSlaver) 
			&& (pow(insect->pos_x - insect->nearlest.second.first, 2) + pow(insect->pos_y - insect->nearlest.second.second, 2) <= 700 )) {
			insect->aim_id = insect->nearlest.first;
			insect->aim_pos = insect->nearlest.second;
			insect->isTriggered = true;
		}
		else {

			pair<int, int> p = { insect->pos_x + rand() % 3 - 1,insect->pos_y + rand() % 3 - 1 };
			int counter = 0;
			int flag = 1;
			while (!(isValidCell(p) && insect->isIndoors(p.first, p.second, field) && isFreeCell(p))) {
				p = { insect->pos_x + rand() % 3 - 1,insect->pos_y + rand() % 3 - 1 };
				counter++;
				if (counter == 5) {
					flag = 0;
					insect->isTriggered = false;
					break;
				}
			}
			if (flag) {
				pair<int, int> lastPos = { insect->pos_x, insect->pos_y };
				moveToCeil(p, id, insect);
				spawnEat(lastPos);

			}
			p = { insect->pos_x, insect->pos_y };
			pair<int, pair<int, int>> prob = { 0, {p.first, p.second} };
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					prob.second = { p.first + i, p.second + j };
					if (!isValidCell(prob.second)) {
						continue;
					}
					else {

					}
					if ((i == j && i == 0) || !insect->isIndoors(prob.second.first, prob.second.second, field) || isFreeCell(prob.second)) continue;
					if (entityList[field->field[prob.second.first][prob.second.second][0].IDs[0]]->getType() == Entities::MATERIALS) {
						//cout << prob.second.first << " : " << prob.second.second << "\n";
						insect->nearlest.first = field->field[prob.second.first][prob.second.second][0].IDs[0];
						insect->nearlest.second = { prob.second.first, prob.second.second };
						if (insect->isSlaver) {
							insect->isSlaveZone = true;
						}
						else {
							insect->isSlaveZone = false;
						}
						//cout << "FUCK CODE RED: " << p.first;
						insect->aim_id = field->field[prob.second.first][prob.second.second][0].IDs[0];
						insect->aim_pos = { prob.second.first, prob.second.second };
						insect->isTriggered = true;
					}
				}
			}
		}

	}
	else if (insect->isTriggered) {
		pair<int, int> newPos2 = { insect->pos_x, insect->pos_y };
		if (field->field[insect->aim_pos.first][insect->aim_pos.second][0].IDs[0] != insect->aim_id) {
			insect->isTriggered = false;
			insect->nearlest.first = 0;
			return;
		}
		if (insect->pos_x < insect->aim_pos.first)
			newPos2.first++;
		else
			newPos2.first--;
		if (insect->pos_y < insect->aim_pos.second)
			newPos2.second++;
		else
			newPos2.second--;
		bool hasMoved = false;
		pair<int, int> lastPos = { insect->pos_x, insect->pos_y };

		if (isValidCell(newPos2) && isFreeCell(newPos2) && insect->isIndoors(newPos2.first, newPos2.second, field)) {
			moveToCeil(newPos2, id, insect);
			hasMoved = true;
		}
		else {
			pair<int, int> p;
			int counter = 0;
			int flag = 1;
			while (!(isValidCell(p = { insect->pos_x + rand() % 3 - 1,insect->pos_y + rand() % 3 - 1 }) && isFreeCell(p) && insect->isIndoors(p.first, p.second, field))) {
				counter++;
				if (counter == 15) {
					flag = 0;
					insect->isTriggered = false;
					break;
				}
			}
			if (flag) {
				moveToCeil(p, id, insect);
				hasMoved = true;
			}
		}
		if (hasMoved) {
			spawnEat(lastPos);
		}

		float vec = pow(insect->aim_pos.first - insect->pos_x, 2) + pow(insect->aim_pos.second - insect->pos_y, 2);
		if (0.95 < vec && vec < 1.1) {
			Materials* currTarget = (Materials*)(entityList[insect->aim_id]->getPtr());
			if (currTarget->hp > 1) {
				currTarget->hp--;
			}
			else {
				if (insect->nearlest.first == insect->aim_id) {
					insect->nearlest.first = 0;
				}
				DeleteEntity(insect->aim_id);
				field->field[insect->aim_pos.first][insect->aim_pos.second][0].IDs[0] = 0;
				insect->isTriggered = false;
			}
		}
	}
}
void InfoSpace::MoveInsect(unsigned int id) {

	Entity* curr = entityList[id];

	Insect* insect = (Insect*)(curr->getPtr());
	if (insect->type == InsectTypes::LADYBUG) {
		MoveLadybug(id, insect);
	}

	if (insect->curState == 1) {
		return;
	}

	if (insect->type == InsectTypes::APHID) {
		MoveAphid(id, insect);
	}
	


	

	
}

//type - 1 = муравей; under_class: 1 = Scout, 2 = Worker, 3 = Soldier, 4 = Nurse, 0 = Queen
bool InfoSpace::CreateEntityAnt(int x, int y, int z, int type, int under_class, int clan) {
	
	if (field->field[x][y][z].IDs[0] != 0)return false;
	if (type == 0) {

		Ant* new_ant;
		if (under_class == 0) {
			new_ant = new Queen(x, y, z, clan);
			coloniesList[clan]->Queen = new_ant;
		}
		else if (under_class == 1) {
			new_ant = new Scout(x, y, z, clan);
		}
		else if (under_class == 2) {
			new_ant = new Worker(x, y, z, clan);
		}
		else if (under_class == 3) {
			new_ant = new Soldier(x, y, z, clan);
		}
		else if (under_class == 4) {
			new_ant = new Nurse(x, y, z, clan);
		}
		else return false;
		Entity* new_ent = new Entity(new_ant, Entities::ANT);

		

		entityList.insert({ free_key, new_ent });
		field->field[new_ant->pos_x][new_ant->pos_y][new_ant->pos_z].IDs[0] = free_key;
		free_key++;
		return true;

	}
	
	
	return false;
}

bool InfoSpace::CreateEntityFood(int x, int y, int z, int type, float food_value, int weight) {
	if (field->field[x][y][z].IDs[0] != 0)return false;
	Food* food = new Food(x, y, z, type, food_value, weight);
	Entity* new_ent = new Entity(food, Entities::FOOD);
	entityList.insert({ free_key, new_ent });

	field->field[food->pos_x][food->pos_y][food->pos_z].IDs[0] = free_key;

	food->entity_id = free_key;

	free_key++;
	return true;
}	
bool InfoSpace::CreateEntityMaterial(int x, int y, int z, int type, int weight) {
	if (field->field[x][y][z].IDs[0] != 0)return false;
	Materials* mat = new Materials(x, y, z, type, weight);
	Entity* new_ent = new Entity(mat, Entities::MATERIALS);
	entityList.insert({ free_key, new_ent });

	field->field[mat->pos_x][mat->pos_y][mat->pos_z].IDs[0] = free_key;

	mat->entity_id = free_key;

	free_key++;
	return true;
}

bool InfoSpace::CreateInsect(int x,int y, int z, InsectTypes type, pair<int, int> stockPos, pair<int, int> stockSize, bool isSlaver)
{	
	if (field->field[x][y][0].IDs[0] != 0)return false;
	if (type == InsectTypes::APHID) {
		Insect* insect = new Insect(type, x, y, z);
		insect->isSlaver = isSlaver;
		insect->stockPos = stockPos;
		insect->stockSize = stockSize;
		Entity* new_ent = new Entity(insect, Entities::INSECT);
		new_ent->pos_x = x;
		new_ent->pos_y = y;
		insect->id = free_key;
		entityList.insert({ free_key, new_ent });
		field->field[insect->pos_x][insect->pos_y][insect->pos_z].IDs[0] = free_key;
		free_key++;
	}
	else if (type == InsectTypes::LADYBUG){
		Insect* insect = new Insect(type, x, y, z);
		Entity* new_ent = new Entity(insect, Entities::INSECT);
		new_ent->pos_x = x;
		new_ent->pos_y = y;
		insect->id = free_key;
		entityList.insert({ free_key, new_ent });
		field->field[insect->pos_x][insect->pos_y][insect->pos_z].IDs[0] = free_key;
		free_key++;
	}
	
	return true;

}

static int timer_born = 500;
bool InfoSpace::CreateEntityMaggot(int x, int y, int z, int clan) {
	if (field->field[x][y][z].IDs[0] != 0)return false;
	Maggot* new_maggot = new Maggot(clan, timer_born, x, y);
	Entity* new_ent = new Entity(new_maggot, Entities::MAGGOTS);
	entityList.insert({ free_key, new_ent });

	field->field[x][y][z].IDs[0] = free_key;

	free_key++;
	return true;
}

bool InfoSpace::CreateStockpile(int x, int y, int z, int wide, int hight, int type, int clan) {

	Stockpile* target;

	for (auto el : stockpileList) {
		target = el.second;
		if (abs(target->pos_x-x)<max(wide, target->size_x)+2 and abs(target->pos_y - y) < max(hight, target->size_y)+2)return false;
	}

	for (int i = x-1; i <= x + wide; i++) {
		for (int j = y-1; j <= y + hight; j++) {
			if (field->field[i][j][z].cWall!=0)return false;
		}
	}



	Stockpile* new_stock = new Stockpile(x, y, z, wide, hight, type, free_stockpile_key, clan);
	field->field[x][y][z].stockID = free_stockpile_key;
	cout << free_stockpile_key;

	stockpileList.insert({ free_stockpile_key, new_stock });


	free_stockpile_key++;

	return true;

}

bool InfoSpace::BuildWall(Ant* cAnt) {
	if (cAnt->inventary == 0 or field->field[cAnt->aim.first][cAnt->aim.second][cAnt->pos_z].cWall!=0)return false;
	if (entityList[cAnt->inventary]->getType() == 3) {
		DeleteEntity(cAnt->inventary);
		cAnt->inventary = 0;
		field->field[cAnt->aim.first][cAnt->aim.second][cAnt->pos_z].CreateWall(1000.0, cAnt->clan);
		return true;
	}
	return false;
}


pair<int, int> InfoSpace::searchmat(int clan) {
	int source = 0;
	int dest = 0;
	for (auto stock : stockpileList) {
		if (stock.second->clan != clan)continue;
		Stockpile* stash = stock.second;
		if (stash->needWalled == true) {
			dest = stash->id;
		}
		if (stash->type == 1 && stash->food_collected > 0) {
			source = stash->id;
		}
	}
	return { source,dest };

}


bool InfoSpace::BornNewAnts(Ant* Queen) {
	if (Queen->type != 0 or Queen->saturation<= Queen->max_Saturation*0.3) {
		return false;
	}
	int whoWillBorn = 0;
	double chance = ((double)(rand()%10))/10;
	

	


	if (CreateEntityMaggot(Queen->pos_x, Queen->pos_y + 1, 0, Queen->clan)) {
		Queen->saturation -= 100;
		return true;
	}

	

	return false;

}

bool InfoSpace::FeedTheQueen(Ant* curAnt) {

	if (curAnt->inventary == 0 or entityList[curAnt->inventary]->getType()!=FOOD)return false;

	Food* curFood = (Food*)entityList[curAnt->inventary]->getPtr();

	Ant* curQueen = coloniesList[curAnt->clan]->Queen;

	if (curQueen == NULL or curFood==NULL)return false;

	curQueen->saturation += curFood->food_value * 1.5;

	DeleteEntity(curAnt->inventary);
	curAnt->inventary = 0;

	return true;


}

void InfoSpace::Hatching(Stockpile* curStock) {

	if (curStock->type != MAGGOT_STOCK or curStock->food_collected==-1) {
		return;
	}
	unsigned int ind;
	for (int i = 0; i < curStock->size_x; i++) {
		for (int j = 0; j < curStock->size_y; j++) {
			if (i + j > curStock->food_collected)return;
			ind = curStock->stuff[i][j];
			if (ind != 0) {
				if (entityList[ind]->getType() != MAGGOTS)continue;
				Maggot* curMaggot = (Maggot*)entityList[ind]->getPtr();
				if (curMaggot->release_timer <= 0) {

					int whoWillBorn=0;
					int rock = rand() % 100;

					if (rock < 3) {
						whoWillBorn = NURSE;
					}
					else if (rock >= 3 and rock < 15) {
						whoWillBorn = WORKER;
					}
					else if (rock >= 15 and rock < 55) {
						whoWillBorn = WORKER;
					}
					else if (rock >= 55) {
						whoWillBorn = SCOUT;
					}
					if (rand() % 100 > 90) {
						coloniesList[curMaggot->clan]->base_radius++;
					}
					CreateEntityAnt(i + curStock->pos_x, j + curStock->pos_y, curStock->pos_z, 0, whoWillBorn, curMaggot->clan);

					curStock->stuff[i][j] = 0;

					if (curStock->food_collected < curStock->size_x * curStock->size_y and curStock->food_collected>0) {
						curStock->stuff[i][j] = curStock->stuff[(curStock->food_collected) % curStock->size_x][(curStock->food_collected)/ curStock->size_y];
						curStock->stuff[(curStock->food_collected) % curStock->size_x][(curStock->food_collected) / curStock->size_y] = 0;
					}
					else if (curStock->food_collected <= 0) {

					}
					else {
						curStock->stuff[i][j] = curStock->stuff[curStock->size_x-1][curStock->size_y-1];
						curStock->stuff[curStock->size_x - 1][curStock->size_y - 1] = 0;
					}
					curStock->food_collected--;

					DeleteEntity(ind);
					ind = 0;
					continue;
					//entityList.erase(ind);
					
				}
				else {
					--curMaggot->release_timer;
				}
			}
		}
	}
}

bool InfoSpace::ChangeEntityPosition(unsigned int ind, int x, int y, int z) {

	if (x < 0 or y < 0 or x>= field_size_x or y>= field_size_y)return false;

	if (field->field[x][y][z].IDs[0] != 0)return false;

	Entity* curEnt = entityList[ind];

	if (curEnt==NULL)return false;

	if (curEnt->getType() == ANT) {
		Ant* curObj = (Ant*)curEnt->getPtr();

		curObj->pos_x = x;
		curObj->pos_y = y;
		curObj->pos_z = z;

		field->field[x][y][z].IDs[0] = ind;

		return true;
	}
	else if (curEnt->getType() == FOOD) {
		Food* curObj = (Food*)curEnt->getPtr();

		curObj->pos_x = x;
		curObj->pos_y = y;
		curObj->pos_z = z;

		field->field[x][y][z].IDs[0] = ind;

		return true;
	}
	else if (curEnt->getType() == MATERIALS) {
		Materials* curObj = (Materials*)curEnt->getPtr();

		curObj->pos_x = x;
		curObj->pos_y = y;
		curObj->pos_z = z;

		field->field[x][y][z].IDs[0] = ind;

		return true;
	}
	else if (curEnt->getType() == MAGGOTS) {
		Maggot* curObj = (Maggot*)curEnt->getPtr();

		/*curObj->pos_x = x;
		curObj->pos_y = y;
		curObj->pos_z = z;*/

		field->field[x][y][z].IDs[0] = ind;

		return true;
	}
	else if (curEnt->getType() == INSECT) {
		Insect* curObj = (Insect*)curEnt->getPtr();

		curObj->pos_x = x;
		curObj->pos_y = y;
		curObj->pos_z = z;
		
		curObj->curState = 2;
		curObj->isTriggered = false;

		field->field[x][y][z].IDs[0] = ind;

		return true;
	}
	return false;
}

bool InfoSpace::TryToDrop(pair<int,int> cord, int id) {
	
	bool flag = false;

	int x = cord.first;
	int y = cord.second;
	int z = 0;

	for (int i = -4; i <= 4 and !flag; i++) {
		for (int j = -4; j <= 4; j++) {
			if (i == 0 and j == 0)continue;
			if (ChangeEntityPosition(id, x+i, y+j, z)) {
				flag = true;
				return true;
			}
		}
	}
	
	return false;

}

bool InfoSpace::TryToDrop(Ant* ant) {

	if (ant->inventary == 0)return false;
	bool flag = false;
	
	unsigned int id = ant->inventary;

	int x = ant->pos_x;
	int y = ant->pos_y;
	int z = ant->pos_z;

	for (int i = -4; i <= 4 and !flag; i++) {
		for (int j = -4; j <= 4; j++) {
			if (i == 0 and j == 0)continue;
			if (ChangeEntityPosition(id, x + i, y + j, z)) {
				flag = true;
				ant->inventary = 0;
				return true;
			}
		}
	}

	return false;

}

double dist(int p1, int p2, int p3, int p4) {
	return (p1 - p3) * (p1 - p3) + (p2 - p4) * (p2 - p4);
}

bool InfoSpace::Picked(unsigned int ind) {

	
	Entity* curEnt = entityList[ind];

	if (curEnt == NULL)return false;

	if (curEnt->getType() == ANT) {
		Ant* curObj = (Ant*)curEnt->getPtr();

		


		return true;
	}
	else if (curEnt->getType() == FOOD) {
		Food* curObj = (Food*)curEnt->getPtr();



		return true;
	}
	else if (curEnt->getType() == MATERIALS) {
		Materials* curObj = (Materials*)curEnt->getPtr();

		

		return true;
	}
	else if (curEnt->getType() == MAGGOTS) {
		Maggot* curObj = (Maggot*)curEnt->getPtr();

		

		return true;
	}
	else if (curEnt->getType() == INSECT) {
		Insect* curObj = (Insect*)curEnt->getPtr();

		curObj->curState = 1;
		curObj->isTriggered = false;
		curObj->isSlaver = true;
		
		return true;
	}
	return false;
}

void InfoSpace::ReCalculateTheColony()
{

	Ant* curAnt;
	Stockpile* curStock;
	int clan; 

	for (auto el : coloniesList) {
		el.second->NullEverything();
	}

	for (auto el : entityList) {
		if (el.second == NULL) { 
			entityList.erase(el.first); 
			continue;
		}
		if (el.second->getType() == ANT) {
			
			curAnt = (Ant*)el.second->getPtr();
			clan = curAnt->clan;
			if (curAnt->type==SCOUT) {
				++coloniesList[clan]->numScouts;
			}
			else if (curAnt->type == WORKER) {
				++coloniesList[clan]->numWorker;
			}
			else if (curAnt->type == SOLDIER) {
				++coloniesList[clan]->numSoldier;
			}
			else if (curAnt->type == NURSE) {
				++coloniesList[clan]->numNurses;
			}

		}

	}

	for (auto el : stockpileList) {
		
		curStock = el.second;
		clan = curStock->clan;
		Colony* curColony = coloniesList[clan];

		if (curStock->type == FOOD_STOCK) {

			curColony->curFoodAmount += curStock->food_collected;

		}
		else if (curStock->type == MATERIAL_STOCK) {

			curColony->curMaterialAmount += curStock->food_collected;

		}
		else if (curStock->type == MAGGOT_STOCK) {

			curColony->curMaggotAmount += curStock->food_collected;

		}

	}
}

//Действия муравейника

void InfoSpace::BuildNewStockpile(Colony* curColony) {
	int tri = rand() % 20 + 4;
	
	if (curColony->needNewFoodStock) {

		int x, y, z;
		int tries = tri;
		int sz = rand() % 20 + 12;
		for (; tries > 0; tries--) {
			
			x = curColony->base_x + rand() % (curColony->base_radius) - curColony->base_radius/2;
			y= curColony->base_y + rand() % (curColony->base_radius) - curColony->base_radius / 2;
			if (CreateStockpile(x, y, 0, sz, sz, 0, curColony->clan)) {
				curColony->needNewFoodStock = false;
				
			}
			
		}
		if (tries == 0 and curColony->needNewFoodStock) {
			curColony->base_radius += curColony->delta_stock;
		}

	}

	if (curColony->needNewMatStock) {

		int x, y, z;
		int tries = tri;
		int sz = rand() % 20 + 12;
		for (; tries > 0; tries--) {

			x = curColony->base_x + rand() % (curColony->base_radius) - curColony->base_radius / 2;
			y = curColony->base_y + rand() % (curColony->base_radius) - curColony->base_radius / 2;
			if (CreateStockpile(x, y, 0, sz, sz, MATERIAL_STOCK, curColony->clan)) {
				curColony->needNewMatStock = false;
				
			}
			
		}
		if (tries == 0 and curColony->needNewMatStock) {
			curColony->base_radius += curColony->delta_stock;
		}

	}

	if (curColony->needNewAphidStock and curColony->numWorker>50) {

		int x, y, z;
		int tries = tri;
		int sz = rand() % 40 + 20;
		for (; tries > 0; tries--) {

			x = curColony->base_x + rand() % (curColony->base_radius) - curColony->base_radius / 2;
			y = curColony->base_y + rand() % (curColony->base_radius) - curColony->base_radius / 2;
			if (CreateStockpile(x, y, 0, sz, sz, APHID_STOCK, curColony->clan)) {
				curColony->needNewAphidStock = false;
				break;
			}
			
		}
		if (tries == 0 and curColony->needNewAphidStock) {
			curColony->base_radius += curColony->delta_stock;
		}

	}

}

void InfoSpace::RecountAphid()
{
	Stockpile* curStock;
	unsigned int id;
	for (auto el : stockpileList) {
		curStock = el.second;

		if (curStock->type == APHID_STOCK) {
			curStock->food_collected = 0;

			for (int x = curStock->pos_x; x < curStock->pos_x + curStock->size_x; x++) {
				for (int y = curStock->pos_y; y < curStock->pos_y + curStock->size_y; y++) {
					bool fl = false;
					id = field->field[x][y][curStock->pos_z].IDs[0];
					if (id != 0 and entityList[id]->getType() == INSECT) {
						curStock->food_collected+=1;
						
					}
					

				}
			}

		}

	}
}


void InfoSpace::attack(int atkr, int defr) {
	if (atkr == defr) { return; }
	Entity* attacker = entityList[atkr];
	Entity* defender = entityList[defr];
	Ant* atkant = (Ant*)attacker->getPtr();
	if (defender->getType() == ANT) {
		Ant* defant = (Ant*)defender->getPtr();
		defant->HP -= atkant->attack;
		if (defant->HP <= 0) {
			DeleteEntity(defr);
			field->field[defant->pos_x][defant->pos_y]->IDs[0]=0;
		}
	}
	if (defender->getType() == INSECT) {
		Insect* defant = (Insect*)defender->getPtr();
		defant->hp -= atkant->attack;
		if (defant->hp <= 0) {
			DeleteEntity(defr);
			field->field[defant->pos_x][defant->pos_y]->IDs[0] = 0;
		}
	}


}





// MOVE

void InfoSpace::MoveEntity(unsigned int id) {
	Entity* curEnt = entityList[id];


	Ant* ant = (Ant *)curEnt->getPtr();

	Colony* curColony = coloniesList[ant->clan];

	if (ant->type == QUEEN) {
		//cout << "HERE" << endl;
		BornNewAnts(ant);

		return;
	}

	if (ant->type > 4) { return; }

	// move 1 turn >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	vector<vector<double>> dt;
	for (double i = -1; i <= 1; i++) {
		for (double j = -1; j <= 1; j++) {
			if (ant->pos_x + i >= 0 and ant->pos_x + i < field_size_x and ant->pos_y + j >= 0 and ant->pos_y + j < field_size_y) {
				dt.push_back({ dist(ant->pos_x + i,  ant->pos_y + j,  ant->aim.first,  ant->aim.second), 1.1+rand()%2 , i , j});
			}
		}
	}	
	sort(dt.begin(), dt.end());
	
	int wh = 0;
	int num = this->field->field[ant->pos_x][ant->pos_y]->CutEntity(0);
	while ((this->field->field[(int)(ant->pos_x + dt[wh][2])][(int)(ant->pos_y + dt[wh][3])]->IDs[0]
		or (this->field->field[(int)(ant->pos_x + dt[wh][2])][(int)(ant->pos_y + dt[wh][3])]->cWall and this->field->field[(int)(ant->pos_x + dt[wh][2])][(int)(ant->pos_y + dt[wh][3])]->cWall->clan!=ant->clan)
		) && wh != 9) {
		wh += 1;
	}
		
	if(wh!=9){
		ant->pos_x += dt[wh][2];
		ant->pos_y += dt[wh][3];
		this->field->field[ant->pos_x][ant->pos_y]->IDs[0] = num;
	}

	// hungrys >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ant->saturation -= 0.02; // randommmmmmmmmmmmm

	if (ant->saturation < 0) {
		ant->HP -= 0.1;
	}

	if (ant->HP < 0) {
		
		field->field[ant->pos_x][ant->pos_y][ant->pos_z].CutEntity(0);
		DeleteEntity(id);
		return;

	}

	

	if (ant->saturation<=ant->max_Saturation*0.3 && ant->action!=3) {
		ant->paction = ant->action;
		ant->paim = ant->aim;
		
		bool relevant = false;
		for (auto stock : stockpileList) {
			Stockpile* stash = stock.second;
			
			if (stash->type == 0 and stash->food_collected>=0 and stash->clan==ant->clan) {
				ant->action = 3;


				if (stash->type == 0 and stash->food_collected == stash->size_x * stash->size_y) {
				}
				int aim_x = stash->pos_x + stash->food_collected % stash->size_x;
				int aim_y = stash->pos_y + stash->food_collected / stash->size_x;
				if (stash->food_collected == stash->size_x * stash->size_y) {
					aim_x = stash->pos_x + stash->size_x - 1;
					aim_y = stash->pos_y + stash->size_y - 1;
				}
				


				if (stash->type == 0 and (!relevant or dist(ant->aim.first, ant->aim.second, ant->pos_x, ant->pos_y)> dist(aim_x, aim_y, ant->pos_x, ant->pos_y))) {
					
					ant->stashid = stash->id;
					cout << stash->id;

					ant->aim = { aim_x,aim_y };
					
					relevant = true;
				}
				
			}
		}
	}

	if (ant->action==3) {
		if (dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 10) {
			cout << "EAT" << endl;
			DeleteEntity(stockpileList[ant->stashid]->AntIslEating(ant, &entityList));
			ant->action = ant->paction;
			if (ant->action == 6) {
				ant->action = 0;
				TryToDrop(ant);
				ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
			}
			ant->aim = ant->paim;
		}
	}

	// scouts >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	else if (ant->type == 1 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <=2) {
		 //ant->aim = { rand() % (this->field_size_x-2)+1,  rand() % (this->field_size_x - 2) + 1 };
		 ant->aim = { (rand() % (curColony->base_radius) - curColony->base_radius/2)* curColony->scouts_courage + curColony->base_x,  (rand() % (curColony->base_radius) - curColony->base_radius / 2) * curColony->scouts_courage + curColony->base_y };
	}

	// workers >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	else if (ant->type == 2 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
		if (ant->inventary != 0 && ant->action<5) {
			for (auto stock : stockpileList) {
				Stockpile* stash = stock.second;

				if (stash->clan != ant->clan)continue;

				bool isValidStock = stash->pos_x <= ant->aim.first and ant->aim.first <= stash->pos_x + stash->size_x and stash->pos_y <= ant->aim.second and ant->aim.second <= stash->pos_y + stash->size_y;
				if (ant->inventary !=0 &&((stash->type==0 && entityList[ant->inventary]->getType() == Entities::FOOD) or (stash->type == 1 && entityList[ant->inventary]->getType() == Entities::MATERIALS)) and isValidStock) {
					stash->TryToPut(ant, &entityList, ant->aim);
					ant->action = 0;
				}
				else if (ant->inventary != 0 && stash->type == 2 && entityList[ant->inventary]->getType() == Entities::INSECT && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= (stash->size_x*stash->size_x)) {
					if (TryToDrop(ant->aim, ant->inventary)) {

						stash->food_collected++;

						ant->inventary = 0;
					}
					ant->action = 0;
					//ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 };

					ant->aim = { rand() % curColony->base_radius - curColony->base_radius/2  + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius /2 + curColony->base_y };

					return;
					break;
				}
				else if(ant->inventary != 0 && stash->type == 0 && entityList[ant->inventary]->getType() == Entities::FOOD and isValidStock) {
					ant->aim = { stash->pos_x + stash->food_collected % stash->size_x,stash->pos_y + stash->food_collected / stash->size_y };
				}
				else if (ant->inventary != 0 && stash->type == 1 && entityList[ant->inventary]->getType() == Entities::MATERIALS and isValidStock) {
					ant->aim = { stash->pos_x + stash->food_collected % stash->size_x,stash->pos_y + stash->food_collected / stash->size_y };
				}
				else if (ant->inventary != 0 && stash->type == 2  && entityList[ant->inventary]->getType() == Entities::INSECT) {
					ant->aim = { stash->pos_x + stash->size_x/2,stash->pos_y + stash->size_y/2 };
				}
			}	
		}
		else if (ant->action == 6 and ant->type == WORKER and ant->stashid != 0 and stockpileList[ant->stashid]->needWalled == false) {
			TryToDrop(ant);
			ant->action = 0;
			ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
		}//КОСТЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЛЬ 1013
		
		else if (ant->inventary == 0 && ant->action == 2) {
			ant->action = 0;
			//ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 };
			ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
		}

		else if ((ant->action == 0 and rand()%10 < 3) or (ant->dest > 0 && ant->dest<stockpileList.size() && stockpileList[ant->dest]->needWalled == false)) {
			pair<int, int> stocks = searchmat(ant->clan);
			ant->source = stocks.first;
			ant->dest = stocks.second;
			
			if (ant->source && ant->dest) {
				ant->action = 4;
				Stockpile* stock = stockpileList[ant->source];
				ant->aim = { stock->pos_x + stock->food_collected % stock->size_x,stock->pos_y + stock->food_collected / stock->size_y };
			}
			else {
				//ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 };
				ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
			}
			
		}
		if (ant->action == 4) {
			Stockpile* stock = stockpileList[ant->source];
			stock->PickUp(ant, &entityList);
			stock = stockpileList[ant->dest];
			ant->aim = { stock->pos_x,stock->pos_y};
			ant->action = 5;
		}
		if (ant->action == 5 or (ant->dest!=0 && ant->action==6 && field->field[ant->aim.first][ant->aim.second]->cWall !=0) ) {
			Stockpile* stock = stockpileList[ant->dest];
			
			int ch = 0;
			for (int i = - 1; i <= stock->size_x; i++) {
				for (int j = - 1; j <= stock->size_y; j++) {
					int ci = i + stock->pos_x;
					int cj = j + stock->pos_y;
					if (ch == 0 && ci==ci%size_x && cj==cj%size_y && (i==-1 or i==stock->size_x or j==-1 or j==stock->size_y) && field->field[ci][cj]->cWall == 0) {
						ant->aim = { ci,cj };
						ant->action = 6;
						ch = 1;
						
					}
				}
			}
			if (ch == 0) {
				//TryToDrop(ant);
				//ant->action = 0;
			}
			
		}
		if (ant->action == 6 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 8 && field->field[ant->pos_x][ant->pos_y]->cWall == 0) {
			if (ant->dest == 0) {
				TryToDrop(ant);
				ant->action = 0;
			}
			else {
				Stockpile* stash = stockpileList[ant->dest];
				if (stash->needWalled == true &&(dist(ant->aim.first, ant->aim.second, stash->pos_x + stash->size_x / 2, stash->pos_y + stash->size_y / 2)<= 3*dist(stash->pos_x + stash->size_x + 1, stash->pos_y + stash->size_y+1, stash->pos_x + stash->size_x / 2, stash->pos_y + stash->size_y / 2)+8)) {
					if (BuildWall(ant)) {
						stash->wall_len += 1;
						if (stash->wall_len == ((stash->size_x + stash->size_y + 2) * 2)) {
							stash->needWalled = false;
						}
						ant->action = 0;
						ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
					}

				}
				else {
					TryToDrop(ant);
					ant->action = 0;
					ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
				}
			}
		
		}
		if (ant->action == 0 and ant->inventary!=0) {
			TryToDrop(ant);
		}
		if (ant->action < 4) {
			//ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 }; // коорды базы
			ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
			ant->action = 0;
		}
	}
	// warriors >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	else if ((ant->type == 3 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2)) {
		//ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 }; // коорды базы
		int entid = field->field[ant->aim.first][ant->aim.second]->IDs[0];
		
		if (entid!=0) {
			attack(id, entid);
		}
		ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
		ant->action = 0;
	}

	// NURSES >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	else if (ant->type == 4) { 
		Ant* Mom = coloniesList[ant->clan]->Queen;
		Entity* mem = entityList[field->field[Mom->pos_x][Mom->pos_y + 1]->IDs[0]];
		if (Mom->saturation <= Mom->max_Saturation * 0.7) {
			if (ant->inventary == 0) {
				unsigned int source = 0;

				
				int distance = INT_MAX;
				int new_distance;

				for (auto stock : stockpileList) {
					if (stock.second->clan != ant->clan or stock.first<=0)continue;

					

					Stockpile* stash = stock.second;
					
					if (stash->type == 0 && stash->food_collected > 0) {
						new_distance = dist(ant->pos_x, ant->pos_y, stash->pos_x, stash->pos_y);
						if (new_distance < distance) {
							distance = new_distance;
							source = stash->id;
						}
					}
					

				}
				ant->source = source;
				if (ant->source) {
					Stockpile* stock = stockpileList[ant->source];
					ant->aim = { stock->pos_x + stock->food_collected % stock->size_x,stock->pos_y + stock->food_collected / stock->size_y };
				}
				if (ant->source && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
					Stockpile* stock = stockpileList[ant->source];
					stock->PickUp(ant, &entityList);
				}
			}
			else if(entityList[ant->inventary]->getType() == Entities::FOOD) {
				ant->aim = {Mom->pos_x,Mom->pos_y };
				if (dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
					FeedTheQueen(ant);
				}
			}
			else if (entityList[ant->inventary]->getType() == Entities::MAGGOTS) {
				int source = 0;
				for (auto stock : stockpileList) {
					Stockpile* stash = stock.second;
					if (stash->type == 3 and stash->clan==ant->clan) {
						source = stash->id;
					}
				}
				ant->source = source;
				if (ant->source) {
					Stockpile* stock = stockpileList[ant->source];
					ant->aim = { stock->pos_x + stock->food_collected % stock->size_x,stock->pos_y + stock->food_collected / stock->size_y };
				}
				if (dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
					Stockpile* stock = stockpileList[ant->source];
					stock->TryToPut(ant, &entityList, ant->aim);
				}
			}
		}
		else if (mem && mem->getType()==Entities::MAGGOTS) {
			ant->aim = { Mom->pos_x,Mom->pos_y + 1 };
			if (dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
				ant->inventary=field->field[Mom->pos_x][Mom->pos_y + 1]->CutEntity(0);
			}
		}
		else  {
			ant->aim = { rand() % 40 - 20 + Mom->pos_x,  rand() % 40 - 20 + Mom->pos_y };
		}
	}


	// scout says >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	if (ant->type == 1) {
		for (double i = -3; i <= 3; i++) {
			for (double j = -3; j <= 3; j++) {
				if (ant->pos_x + i >= 0 and ant->pos_x + i < field_size_x and ant->pos_y + j >= 0 and ant->pos_y + j < field_size_y) {
					if (this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]) {
						Entity* obj = entityList[this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]];

						
						if (obj and obj->getType() == Entities::FOOD) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							//ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
							ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
							ant->action = 1;
							
						}
						if (obj and obj->getType() == Entities::INSECT) {
							Insect* smth = (Insect*)obj->getPtr();
							if (smth->curState == 0 and smth->type==APHID and smth->curState==0) {
								ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
								//ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
								ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
								ant->action = 1;
							} 
							if (smth->curState == 0 and smth->type == LADYBUG  and smth->curState == 0) {
								ant->nearest_En = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
								//ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
								ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
								ant->action = 1;
							}

						}
						if (obj and obj->getType() == Entities::MATERIALS) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							//ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
							ant->aim = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
							ant->action = 1;

						}
						else if (obj and obj->getType() == Entities::ANT) {
							Ant* smth = (Ant*)obj->getPtr();
							if (smth == NULL)continue;
							if ( ant->clan != smth->clan) {
								ant->nearest_En = {smth->pos_x, smth->pos_y};
								smth->nearest_En = { ant->pos_x, ant->pos_y };
							}
							if (smth->type == 2  && ant->action == 1 && smth->action <= 1  && ant->clan==smth->clan) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Fd;
								
							}
							if (smth->type == 3 && ant->action == 1 && smth->action <= 1 && ant->clan == smth->clan) {
								smth->nearest_En = ant->nearest_En;
								smth->action = 4;
								smth->aim = ant->nearest_En;
								
							}
						}
						
						
					}
				}
			}
		}
	}

	// runners says >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	if (ant->type == 2 or ant->type == 3) {
		for (double i = -1; i <= 1; i++) {
			for (double j = -1; j <= 1; j++) {
				if (ant->pos_x + i >= 0 and ant->pos_x + i < field_size_x and ant->pos_y + j >= 0 and ant->pos_y + j < field_size_y) {
					if (this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]) {
						Entity* obj = entityList[this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]];

						if (obj and obj->getType() == Entities::MATERIALS && ant->type == 2 && ant->action < 2) {
							ant->nearest_Mat = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };

							pair<int, int> na = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
							bool transporting_need = false;

							for (auto stock : stockpileList) {
								if (stock.second->clan==ant->clan and stock.second->type == 1 && stock.second->food_collected < stock.second->size_x * stock.second->size_y) {
									
									if (!transporting_need or dist(na.first, na.second, ant->pos_x, ant->pos_y) > dist(stock.second->pos_x, stock.second->pos_y, ant->pos_x, ant->pos_y)) {
										if (stock.second->food_collected < 0) {
											na = { stock.second->pos_x ,stock.second->pos_y };
										}
										else {
											na = { stock.second->pos_x + stock.second->food_collected % stock.second->size_x,stock.second->pos_y + stock.second->food_collected / stock.second->size_y };
										}
									}
									transporting_need = true;

								}
							}

							if (ant->inventary == 0 and transporting_need) {
								ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								Picked(ant->inventary);
								//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
							}
							else if (transporting_need == false) {
								curColony->needNewMatStock = true;
							}
							

							if (ant->action != 6) {
								ant->aim = na;
								ant->action = 2;
							}
						}
						else if (obj and obj->getType() == Entities::FOOD && ant->type == 2 && ant->action < 2) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };

							pair<int, int> na = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
							bool transporting_need = false;
							for (auto stock : stockpileList) {
								if (stock.second->clan == ant->clan and stock.second->type == 0 && stock.second->food_collected != stock.second->size_x * stock.second->size_y) {
									
									if (!transporting_need or dist(na.first, na.second, ant->pos_x, ant->pos_y) > dist(stock.second->pos_x, stock.second->pos_y, ant->pos_x, ant->pos_y)) {
										if (stock.second->food_collected < 0) {
											na = { stock.second->pos_x ,stock.second->pos_y };
										}
										else {
											na = { stock.second->pos_x + stock.second->food_collected % stock.second->size_x,stock.second->pos_y + stock.second->food_collected / stock.second->size_y };
										}
									}
									transporting_need = true;

								}
							}

							if (ant->inventary == 0 and transporting_need==true) {
								ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
							}
							else if(transporting_need==false){
								curColony->needNewFoodStock = true;
							}
							//pair<int, int> na = { rand() % 20 + 1,  rand() % 20 + 1 };
							
							ant->aim = na;
							ant->action = 2;
						}
						else if (obj and obj->getType() == Entities::INSECT && ant->type == 2 && ant->action < 2) {

							bool transporting_need = false;
							bool isPrepearing = false;

							Insect* smth = (Insect*)obj->getPtr();
							if (smth->type == APHID) {
								pair<int, int> na = { rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_x,  rand() % curColony->base_radius - curColony->base_radius / 2 + curColony->base_y };
								for (auto stock : stockpileList) {
									if (stock.second->clan != ant->clan)continue;
									if (stock.second->type == 2 and stock.second->needWalled == true) {
										isPrepearing = true;
									}
									if (stock.second->type == 2 and stock.second->needWalled == false && stock.second->food_collected < stock.second->size_x / 2) {
										na = { stock.second->pos_x + stock.second->size_x / 2,stock.second->pos_y + stock.second->size_y / 2 };
										transporting_need = true;
										isPrepearing = false;
									}

								}

								if (transporting_need) {
									ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };

									if (ant->inventary == 0 && smth->curState == 0) {
										ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
										Picked(ant->inventary);
										//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
									}


									ant->action = 2;
								}
								else {
									ant->action = 0;
									if (isPrepearing == false) {
										curColony->needNewAphidStock = true;
									}
								}
								ant->aim = na;
							}
						}
						
						else if (obj and obj->getType() == Entities::ANT) {
							Ant* smth = (Ant*)obj->getPtr();
							if ( ant->clan == smth->clan &&smth->type == 2  && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_Fd.first, ant->nearest_Fd.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_Fd.first, smth->nearest_Fd.second))) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Fd;
								
							}
							if (ant->clan != smth->clan) {
								ant->nearest_En = { smth->pos_x, smth->pos_y };
								smth->nearest_En = { ant->pos_x, ant->pos_y };
							}
							if (ant->clan == smth->clan && smth->type == 2  && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_Mat.first, ant->nearest_Mat.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_Mat.first, smth->nearest_Mat.second))) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Mat;
								
							}
							if (ant->clan == smth->clan && smth->type == 3  && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_En.first, ant->nearest_En.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_En.first, smth->nearest_En.second))) {
								smth->nearest_En = ant->nearest_En;
								smth->action = 4;
								smth->aim = ant->nearest_En;
								

							}
						}
					}
				}
			}
		}

	}

	
	
}


bool InfoSpace::DeleteEntity(unsigned int id) {
	if (id == 0) {
		return false;
	}
	Entity* curEnt = entityList[id];
	entityList.erase(id);
	
	

	if(curEnt->getType() == FOOD) {//еда

		Food* curFood = (Food*)(curEnt->getPtr());


		delete curFood;
	}
	else if (curEnt->getType() == ANT) {//еда
		Ant* curAnt = (Ant*)(curEnt->getPtr());

		coloniesList[curAnt->clan]->died++;

		delete curAnt;
		
	}
	else if (curEnt->getType() == MATERIALS) {
		Materials* curMat = (Materials*)(curEnt->getPtr());

		delete curMat;
	}
	else if (curEnt->getType() == MAGGOTS) {
		Maggot* curMag = (Maggot*)(curEnt->getPtr());

		delete curMag;
	}
	return false;
}
void InfoSpace::MoveCam(int x_d, int y_d) {
	x_cam += x_d*cam_speed;
	y_cam += y_d*cam_speed;
	if (x_cam < 0)x_cam = 0;
	else if (x_cam > field_size_x*cell_size - main_window_wide)x_cam =x_cam-cam_speed;
	if (y_cam < 0)y_cam = 0;
	else if (y_cam > field_size_y*cell_size - main_window_hight)y_cam = y_cam-cam_speed;
}