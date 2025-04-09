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
			if (flag) moveToCeil(p, id, curr);

			pair<int, pair<int, int>> prob = { 0, {p.first, p.second} };
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					prob.second = { p.first + i, p.second + j };
					if (!isValidCell(prob.second)) continue;
					if ((i == j && i == 0) || !insect->isIndoors(prob.second.first, prob.second.second, field) || isFreeCell(prob.second)) continue;
					if (entityList[field->field[prob.second.first][prob.second.second][0].IDs[0]]->getType() == Entities::MATERIALS) {
						insect->nearlest.first = field->field[prob.second.first][prob.second.second][0].IDs[0];
						insect->nearlest.second = { prob.second.first, prob.second.second };
						if (insect->isSlaver) {
							insect->isSlaveZone = true;
						}
						else {
							insect->isSlaveZone = false;
						}
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

		if (isValidCell(newPos2) && isFreeCell(newPos2) && insect->isIndoors(newPos2.first, newPos2.second, field)) {
			moveToCeil(newPos2, id, curr);
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
			if (flag) moveToCeil(p, id, curr);
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
	Food* food = new Food(x, y, z, type, food_value, weight);
	Entity* new_ent = new Entity(food, Entities::FOOD);
	entityList.insert({ free_key, new_ent });

	field->field[food->pos_x][food->pos_y][food->pos_z].IDs[0] = free_key;

	food->entity_id = free_key;

	free_key++;
	return true;
}	
bool InfoSpace::CreateEntityMaterial(int x, int y, int z, int type, int weight) {
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

	if (cAnt->inventary == 0)return 0;

	if (entityList[cAnt->inventary]->getType() == 3) {
		DeleteEntity(cAnt->inventary);
		cAnt->inventary = 0;

		field->field[cAnt->pos_x][cAnt->pos_y][cAnt->pos_z].CreateWall(1000.0, cAnt->clan);

	}

}



double dist(int p1, int p2, int p3, int p4) {
	return (p1 - p3) * (p1 - p3) + (p2 - p4) * (p2 - p4);
}



// MOVE
void InfoSpace::MoveEntity(unsigned int id) {
	Entity* curEnt = entityList[id];


	Ant* ant = (Ant *)curEnt->getPtr();


	if (ant->type > 3) { return; }
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
	ant->saturation -= 0.2;
	if (ant->saturation < 0) {
		cout << "dead" << ant->type<< endl;
	}
	if (ant->saturation<=ant->max_Saturation*0.3 && ant->action!=3) {
		
		for (auto stock : stockpileList) {
			Stockpile* stash = stock.second;
			
			if (stash->type == 0 and stash->food_collected>=0) {
				ant->action = 3;
				int aim_x = stash->pos_x + stash->food_collected % stash->size_x;
				int aim_y = stash->pos_y + stash->food_collected / stash->size_x;
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
			ant->action = 0;
		}
	}
	else if (ant->type == 1 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <=2) {
		 ant->aim = { rand() % (this->field_size_x-2)+1,  rand() % (this->field_size_x - 2) + 1 };
	}
	else if (ant->type == 2 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
		if (ant->inventary != 0) {
			for (auto stock : stockpileList) {
				Stockpile* stash = stock.second;
				if (ant->inventary !=0 &&((stash->type==0 && entityList[ant->inventary]->getType() == Entities::FOOD) or (stash->type == 1 && entityList[ant->inventary]->getType() == Entities::MATERIALS)) and stash->pos_x <= ant->aim.first and ant->aim.first <= stash->pos_x + stash->size_x and stash->pos_y <= ant->aim.second and ant->aim.second <= stash->pos_y + stash->size_y) {
					stash->TryToPut(ant, &entityList, ant->aim);
					cout << 2;
				}
			}
			
				
		}
		ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 }; // коорды базы
		ant->action = 0;
	}
	else if (ant->type == 3 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.first) <= 2) {
		ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 }; // коорды базы
		ant->action = 0;
	}


	

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
						if (obj->getType() == Entities::MATERIALS) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
							ant->action = 1;

						}
						/*if (smth->type == 5) {
							ant->nearest_En = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->aim = { rand() % 50 + 1,  rand() % 50 + 1 };
							ant->action = 1;
		
						}*/
						else if (obj->getType() == Entities::ANT) {
							Ant* smth = (Ant*)obj->getPtr();
							if (smth == NULL)continue;
							if (smth->type == 2  && ant->action == 1 && smth->action <= 1 ) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Fd;
								smth->action = 1;
							}
							if (smth->type == 3 && ant->action == 1 && smth->action <= 1) {
								smth->nearest_En = ant->nearest_En;
								smth->aim = ant->nearest_En;
								smth->action = 1;
							}
						}
						
						
					}
				}
			}
		}
	}


	if (ant->type == 2 or ant->type == 3) {
		for (double i = -1; i <= 1; i++) {
			for (double j = -1; j <= 1; j++) {
				if (ant->pos_x + i >= 0 and ant->pos_x + i < field_size_x and ant->pos_y + j >= 0 and ant->pos_y + j < field_size_y) {
					if (this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]) {
						Entity* obj = entityList[this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]];
						
						if (obj->getType() == Entities::FOOD && ant->type == 2 && ant->action != 2) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };

							if (ant->inventary == 0) {
								ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								cout << "I picked food number " << ant->inventary << endl;//подбор еды
								//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
							}
							pair<int, int> na = { rand() % 20 + 1,  rand() % 20 + 1 };
							for (auto stock : stockpileList) {
								if (stock.second->type == 0 && stock.second->food_collected!= stock.second->size_x* stock.second->size_y) {
									cout << "Illbeback" << endl;
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
						else if (obj->getType() == Entities::MATERIALS && ant->type == 2 && ant->action != 2) {
							ant->nearest_Mat = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };

							if (ant->inventary == 0) {
								ant->inventary = this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								cout << "I picked Mat number " << ant->inventary << endl;//подбор еды
								//this->CreateEntityFood(rand() % 100 + 50, rand() % 100 + 50, 0, 0, 10, 10);
							}
							pair<int, int> na = { rand() % 20 + 1,  rand() % 20 + 1 };
							for (auto stock : stockpileList) {
								if (stock.second->type == 1 && stock.second->food_collected != stock.second->size_x * stock.second->size_y) {
									cout << "Illbeback" << endl;
									if (stock.second->food_collected < 0) {
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
						else if (obj->getType() == Entities::ANT) {
							Ant* smth = (Ant*)obj->getPtr();
							if (smth->type == 5 && ant->type == 3) {
								ant->aim = { rand() % 20 + 1,  rand() % 20 + 1 }; // коорды базы
								this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->CutEntity(0);
								ant->action = 1;
							}
							if (smth->type == 2 && ant->action == 1 && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_Fd.first, ant->nearest_Fd.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_Fd.first, smth->nearest_Fd.second))) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Fd;
								smth->action = 1;
							}
							if (smth->type == 2 && ant->action == 1 && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_Mat.first, ant->nearest_Mat.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_Mat.first, smth->nearest_Mat.second))) {
								smth->nearest_Fd = ant->nearest_Fd;
								smth->aim = ant->nearest_Mat;
								smth->action = 1;
							}
							if (smth->type == 3 && ant->action == 1 && smth->action == 0 && (dist(smth->pos_x, smth->pos_y, ant->nearest_En.first, ant->nearest_En.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_En.first, smth->nearest_En.second))) {
								smth->nearest_En = ant->nearest_En;
								smth->aim = ant->nearest_En;
								smth->action = 1;

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