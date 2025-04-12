#include "InfoSpace.h"
#include <algorithm>
#include "Insect.h"
#include <queue>
using namespace std;





bool InfoSpace::isValidCell(pair<int, int> newPos) {
	//return !(newPos.first >= field_size_x || newPos.second >= field_size_y
	//	|| newPos.first < 0 || newPos.second < 0);
	return !(newPos.first >= field_size_x || newPos.second >= field_size_y
		|| newPos.first < 0 || newPos.second < 0);
}
bool InfoSpace::isFreeCell(pair<int, int> newPos2) {
	return field->field[newPos2.first][newPos2.second][0].IDs[0] == 0;
}

void InfoSpace::moveToCeil(pair<int, int> newPos2, unsigned int id, Entity* curr) {
	field->field[curr->pos_x][curr->pos_y][0].IDs[0] = 0;
	field->field[newPos2.first][newPos2.second][0].IDs[0] = id;
	curr->pos_x = newPos2.first;
	curr->pos_y = newPos2.second;
}

void InfoSpace::MoveInsect(unsigned int id) {

	Entity* curr = entityList[id];

	Insect* insect = (Insect*)(curr->getPtr());
	
	if (!insect->isTriggered) {
		
		if (insect->nearlest.first != 0 && (insect->isSlaveZone == insect->isSlaver)) {
			insect->aim_id = insect->nearlest.first;
			insect->aim_pos = insect->nearlest.second;
			insect->isTriggered = true;
		}
		else {
			
			pair<int, int> p = { curr->pos_x + rand() % 3 - 1,curr->pos_y + rand() % 3 - 1 };
			int counter = 0;
			int flag = 1;
			while (!(isValidCell(p) &&  insect->isIndoors(p.first, p.second, field) && isFreeCell(p))) {
				p = { curr->pos_x + rand() % 3 - 1,curr->pos_y + rand() % 3 - 1 };
				counter++;
				if (counter == 5) {
					flag = 0;
					insect->isTriggered = false;
					break;
				}
			}
			if (flag) {
				pair<int, int> lastPos = { curr->pos_x, curr->pos_y };
				moveToCeil(p, id, curr);
				spawnEat(lastPos);

			}
			p = { curr->pos_x, curr->pos_y };
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
		pair<int, int> newPos2 = { curr->pos_x, curr->pos_y };
		if (field->field[insect->aim_pos.first][insect->aim_pos.second][0].IDs[0] != insect->aim_id) {
			insect->isTriggered = false;
			insect->nearlest.first = 0;
			return;
		}
		if (curr->pos_x < insect->aim_pos.first)
			newPos2.first++;
		else
			newPos2.first--;
		if (curr->pos_y < insect->aim_pos.second)
			newPos2.second++;
		else
			newPos2.second--;
		bool hasMoved = false;
		pair<int, int> lastPos = { curr->pos_x, curr->pos_y };

		if (isValidCell(newPos2) && isFreeCell(newPos2) && insect->isIndoors(newPos2.first, newPos2.second, field)) {
			moveToCeil(newPos2, id, curr);
			hasMoved = true;
		}
		else {
			pair<int, int> p;
			int counter = 0;
			int flag = 1;
			while (!(isValidCell(p = { curr->pos_x + rand() % 3 - 1,curr->pos_y + rand() % 3 - 1 }) && isFreeCell(p) && insect->isIndoors(p.first, p.second, field))) {
				counter++;
				if (counter == 15) {
					flag = 0;
					insect->isTriggered = false;
					break;
				}
			}
			if (flag) {
				moveToCeil(p, id, curr);
				hasMoved = true;
			}
		}
		if (hasMoved) {
			spawnEat(lastPos);
		}

		float vec = pow(insect->aim_pos.first - curr->pos_x, 2) + pow(insect->aim_pos.second - curr->pos_y, 2);
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

//type - 1 = муравей; under_class: 1 = Scout, 2 = Worker, 3 = Soldier, 0 = Queen
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

	for (int i = x; i < x + wide; i++) {
		for (int j = y; j < y + hight; j++) {
			if (field->field[i][j]->cWall)return false;
		}
	}
	Stockpile* new_stock = new Stockpile(x, y, z, wide, hight, type, free_stockpile_key, clan);
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


pair<int, int> InfoSpace::searchmat() {
	int source = 0;
	int dest = 0;
	for (auto stock : stockpileList) {
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
					CreateEntityAnt(i + curStock->pos_x, j + curStock->pos_y, curStock->pos_z, 0, 1, curMaggot->clan);

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
		
		curObj->curState = 0;
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

	for (int i = -2; i <= 2 and !flag; i++) {
		for (int j = -2; j <= 2; j++) {
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

	for (int i = -2; i <= 2 and !flag; i++) {
		for (int j = -2; j <= 2; j++) {
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
		curObj->isTriggered = true;

		return true;
	}
	return false;
}

// MOVE

void InfoSpace::MoveEntity(unsigned int id) {
	Entity* curEnt = entityList[id];


	Ant* ant = (Ant *)curEnt->getPtr();

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
	while (this->field->field[(int)(ant->pos_x + dt[wh][2])][(int)(ant->pos_y + dt[wh][3])]->IDs[0] && wh != 9) {
		wh += 1;
	}
		
	if(wh!=9){
		ant->pos_x += dt[wh][2];
		ant->pos_y += dt[wh][3];
		this->field->field[ant->pos_x][ant->pos_y]->IDs[0] = num;
	}

	// hungrys >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ant->saturation -= 0.2; // randommmmmmmmmmmmm

	if (ant->saturation < 0) {
		cout << "dead" << ant->type<< endl;
	}

	

	if (ant->saturation<=ant->max_Saturation*0.3 && ant->action!=3) {
		ant->paction = ant->action;
		ant->paim = ant->aim;
		
		for (auto stock : stockpileList) {
			Stockpile* stash = stock.second;
			
			if (stash->type == 0 and stash->food_collected>=0) {
				ant->action = 3;
				if (stash->food_collected == stash->size_x * stash->size_y) {
				}
				int aim_x = stash->pos_x + stash->food_collected % stash->size_x;
				int aim_y = stash->pos_y + stash->food_collected / stash->size_x;
				if (stash->food_collected == stash->size_x * stash->size_y) {
					aim_x = stash->pos_x + stash->size_x - 1;
					aim_y = stash->pos_y + stash->size_y - 1;
				}
				ant->stashid = stash->id;
				cout << stash->id;
				if (ant->type == 3) {
					ant->nearest_En = { aim_x,aim_y };
					ant->aim = { aim_x,aim_y };
				}
				else {
					ant->aim = { aim_x,aim_y };
				}
				
				
			}
		}
	}

	if (ant->action==3) {
		if (dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
			cout << "EAT" << endl;
			DeleteEntity(stockpileList[ant->stashid]->AntIslEating(ant, &entityList));
			ant->action = ant->paction;
			ant->aim = ant->paim;
		}
	}

	// scouts >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	else if (ant->type == 1 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <=2) {
		 ant->aim = { rand() % (this->field_size_x-2)+1,  rand() % (this->field_size_x - 2) + 1 };
	}

	// workers >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	else if (ant->type == 2 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
		if (ant->inventary != 0 && ant->action<5) {
			for (auto stock : stockpileList) {
				Stockpile* stash = stock.second;
				if (ant->inventary !=0 &&((stash->type==0 && entityList[ant->inventary]->getType() == Entities::FOOD) or (stash->type == 1 && entityList[ant->inventary]->getType() == Entities::MATERIALS)) and stash->pos_x <= ant->aim.first and ant->aim.first <= stash->pos_x + stash->size_x and stash->pos_y <= ant->aim.second and ant->aim.second <= stash->pos_y + stash->size_y) {
					stash->TryToPut(ant, &entityList, ant->aim);
					ant->action = 0;
				}
				else if (ant->inventary != 0 && stash->type == 2 && entityList[ant->inventary]->getType() == Entities::INSECT && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= (stash->size_x*stash->size_x)) {
					if (TryToDrop(ant->aim, ant->inventary)) {
						ant->inventary = 0;
					}
					ant->action = 0;
				}
				else if(ant->inventary != 0 && stash->type == 0 && entityList[ant->inventary]->getType() == Entities::FOOD) {
					ant->aim = { stash->pos_x + stash->food_collected % stash->size_x,stash->pos_y + stash->food_collected / stash->size_y };
				}
				else if (ant->inventary != 0 && stash->type == 1 && entityList[ant->inventary]->getType() == Entities::MATERIALS) {
					ant->aim = { stash->pos_x + stash->food_collected % stash->size_x,stash->pos_y + stash->food_collected / stash->size_y };
				}
				else if (ant->inventary != 0 && stash->type == 2 && entityList[ant->inventary]->getType() == Entities::INSECT) {
					ant->aim = { stash->pos_x + stash->size_x/2,stash->pos_y + stash->size_y/2 };
				}
			}	
		}
		

		if (ant->action == 0 or (ant->dest != 0 && stockpileList[ant->dest]->needWalled == false)) {
			pair<int, int> stocks = searchmat();
			ant->source = stocks.first;
			ant->dest = stocks.second;
			
			if (ant->source && ant->dest) {
				ant->action = 4;
				Stockpile* stock = stockpileList[ant->source];
				ant->aim = { stock->pos_x + stock->food_collected % stock->size_x,stock->pos_y + stock->food_collected / stock->size_y };
			}
			else {
				ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 };
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
			
		}
		if (ant->action == 6 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 8 && field->field[ant->pos_x][ant->pos_y]->cWall == 0) {
			if (ant->dest == 0) { return; }
			else {
				Stockpile* stash = stockpileList[ant->dest];
				if (stash->needWalled == true &&(dist(ant->aim.first, ant->aim.second, stash->pos_x + stash->size_x / 2, stash->pos_y + stash->size_y / 2)<= dist(stash->pos_x + stash->size_x + 1, stash->pos_y + stash->size_y+1, stash->pos_x + stash->size_x / 2, stash->pos_y + stash->size_y / 2))) {
					if (BuildWall(ant)) {
						stash->wall_len += 1;
						if (stash->wall_len == ((stash->size_x + stash->size_y + 2) * 2)) {
							stash->needWalled = false;
						}
						ant->action = 0;
					}
				}
				else {
					ant->action = 0;
				}
			}
		
		}
		if (ant->action < 4) {
			ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 }; // коорды базы
			ant->action = 0;
		}
	}

	// warriors >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	else if (ant->type == 3 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
		ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 }; // коорды базы
		ant->action = 0;
	}

	// NURSES >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	else if (ant->type == 4) { 
		Ant* Mom = coloniesList[ant->clan]->Queen;
		Entity* mem = entityList[field->field[Mom->pos_x][Mom->pos_y + 1]->IDs[0]];
		if (Mom->saturation <= Mom->max_Saturation * 0.7) {
			if (ant->inventary == 0) {
				int source = 0;
				for (auto stock : stockpileList) {
					Stockpile* stash = stock.second;
					if (stash->type == 0 && stash->food_collected > 0) {
						source = stash->id;
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
					if (stash->type == 3) {
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

						
						if (obj->getType() == Entities::FOOD) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
							ant->action = 1;
							
						}
						if (obj->getType() == Entities::INSECT) {
							Insect* smth = (Insect*)obj->getPtr();
							if (smth->curState == 0) {
								ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
								ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
								ant->action = 1;
							} 

						}
						if (obj->getType() == Entities::MATERIALS) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
							ant->action = 1;

						}
						else if (obj->getType() == Entities::ANT) {
							Ant* smth = (Ant*)obj->getPtr();
							if (smth == NULL)continue;
							if (ant->action == 1 && smth->action <= 1 && ant->clan != smth->clan) {
								ant->nearest_En = {smth->pos_x, smth->pos_y};
								smth->nearest_En = { ant->pos_x, ant->pos_y };
							}
							if (smth->type == 2  && ant->action == 1 && smth->action <= 1  && ant->clan==smth->clan) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Fd;
								
							}
							if (smth->type == 3 && ant->action == 1 && smth->action <= 1 && ant->clan == smth->clan) {
								smth->nearest_En = ant->nearest_En;
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

						if (obj->getType() == Entities::MATERIALS && ant->type == 2 && ant->action < 2) {
							ant->nearest_Mat = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };

							if (ant->inventary == 0) {
								ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								Picked(ant->inventary);

								

								//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
							}
							pair<int, int> na = { rand() % 20 + 1,  rand() % 20 + 1 };
							for (auto stock : stockpileList) {
								if (stock.second->type == 1 && stock.second->food_collected != stock.second->size_x * stock.second->size_y) {
									if (stock.second->food_collected < 0) {
										na = { stock.second->pos_x + 0 % stock.second->size_x,stock.second->pos_y + 0 / stock.second->size_y };
									}
									else {
										na = { stock.second->pos_x + stock.second->food_collected % stock.second->size_x,stock.second->pos_y + stock.second->food_collected / stock.second->size_y };
									}

								}
							}

							if (ant->action != 6) {
								ant->aim = na;
								ant->action = 2;
							}
						}
						else if (obj->getType() == Entities::FOOD && ant->type == 2 && ant->action < 2) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };

							if (ant->inventary == 0) {
								ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
							}
							pair<int, int> na = { rand() % 20 + 1,  rand() % 20 + 1 };
							for (auto stock : stockpileList) {
								if (stock.second->type == 0 && stock.second->food_collected!= stock.second->size_x* stock.second->size_y) {
									if (stock.second->food_collected <0) {
										na = { stock.second->pos_x + 0 % stock.second->size_x,stock.second->pos_y + 0 / stock.second->size_y };
									}
									else {
										na = { stock.second->pos_x + stock.second->food_collected % stock.second->size_x,stock.second->pos_y + stock.second->food_collected / stock.second->size_y };
									}

								}
							}
							ant->aim = na;
							ant->action = 2;
						}
						else if (obj->getType() == Entities::INSECT && ant->type == 2 && ant->action < 2) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							Insect* smth = (Insect*)obj->getPtr();
							if (ant->inventary == 0 && smth->curState == 0) {
								ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
							}
							pair<int, int> na = { rand() % 20 + 1,  rand() % 20 + 1 };
							for (auto stock : stockpileList) {
								if (stock.second->type == 2 && stock.second->food_collected != stock.second->size_x * stock.second->size_y) {
									na = { stock.second->pos_x + stock.second->size_x/2,stock.second->pos_y + stock.second->size_y/2 };
								}
							}
							ant->aim = na;
							ant->action = 2;
						}
						
						else if (obj->getType() == Entities::ANT) {
							Ant* smth = (Ant*)obj->getPtr();
							if ( ant->clan == smth->clan &&smth->type == 2  && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_Fd.first, ant->nearest_Fd.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_Fd.first, smth->nearest_Fd.second))) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Fd;
								
							}
							if (smth->action <= 1 && ant->clan != smth->clan) {
								ant->nearest_En = { smth->pos_x, smth->pos_y };
								smth->nearest_En = { ant->pos_x, ant->pos_y };
							}
							if (ant->clan == smth->clan && smth->type == 2  && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_Mat.first, ant->nearest_Mat.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_Mat.first, smth->nearest_Mat.second))) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Mat;
								
							}
							if (ant->clan == smth->clan && smth->type == 3  && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_En.first, ant->nearest_En.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_En.first, smth->nearest_En.second))) {
								smth->nearest_En = ant->nearest_En;
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