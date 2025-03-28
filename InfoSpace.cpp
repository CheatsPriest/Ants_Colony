#include "InfoSpace.h"
#include <algorithm>


//type - 1 = муравей; under_class: 1 = Scout, 2 = Worker, 3 = Soldier, 0 = Queen

bool InfoSpace::CreateEntityAnt(int x, int y, int z, int type, int under_class) {
	
	if (field->field[x][y][z].IDs[0] != 0)return false;
	if (type == 0) {

		Ant* new_ant;
		if (under_class == 0) {
			new_ant = new Queen(x, y, z);
		}
		else if (under_class == 1) {
			new_ant = new Scout(x, y, z);
		}
		else if (under_class == 2) {
			new_ant = new Worker(x, y, z);
		}
		else if (under_class == 3) {
			new_ant = new Soldier(x, y, z);
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
bool InfoSpace::CreateEntity(int x, int y, int z, int type, float food_value, int weight){
	Food* food = new Food(x, y, z, type, food_value, weight);
	Entity* new_ent = new Entity(food, Entities::FOOD);
	entityList.insert({ free_key, new_ent });
	food->entity_id = free_key;
	cout << free_key;
	free_key++;
	return true;
}

bool InfoSpace::CreateEntity(int x, int y, int t)
{
	if (field->field[x][y][0].IDs[0] != 0)return false;
	Ant* new_ant;
	new_ant = new Ant(x, y, 0, t,1,1,1,1);
	Entity* new_ent = new Entity(new_ant, Entities::ANT);
	


	entityList.insert({ free_key, new_ent });
	field->field[new_ant->pos_x][new_ant->pos_y][new_ant->pos_z].IDs[0] = free_key;
	cout << free_key;
	free_key++;
	return true;

	
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
	vector<vector<double>> de;
	for (double i = -1; i <= 1; i++) {
		for (double j = -1; j <= 1; j++) {
			if (!(ant->pos_x + i < 0 or ant->pos_x + i >= field_size_x or ant->pos_y + j < 0 or ant->pos_y + j >= field_size_y)) {
				dt.push_back({ dist(ant->pos_x + i,  ant->pos_y + j,  ant->aim.first,  ant->aim.second), -dist(ant->pos_x + i,  ant->pos_y + j,  ant->nearest_En.first,  ant->nearest_En.second) , i , j });
				de.push_back({ dist(ant->pos_x + i,  ant->pos_y + j,  ant->nearest_En.first,  ant->nearest_En.second) , 1, i , j });
			}
		}
	}	
	sort(dt.begin(), dt.end());
	sort(de.begin(), de.end());
	int wh = 0;
	if (ant->type == 3) {

		int num = this->field->field[ant->pos_x][ant->pos_y]->CutEntity(0);
		while (this->field->field[(int)(ant->pos_x + de[wh][2])][(int)(ant->pos_y + de[wh][3])]->IDs[0] && wh != 9) {
			wh += 1;
		}
		if(wh!=9){
			ant->pos_x += de[wh][2];
			ant->pos_y += de[wh][3];
			this->field->field[ant->pos_x][ant->pos_y]->IDs[0] = num;
		}
	}
	else {
		int num = this->field->field[ant->pos_x][ant->pos_y]->CutEntity(0);
		while (this->field->field[(int)(ant->pos_x + dt[wh][2])][(int)(ant->pos_y + dt[wh][3])]->IDs[0] && wh != 9) {
			wh += 1;
		}
		
		if(wh!=9){
			ant->pos_x += dt[wh][2];
			ant->pos_y += dt[wh][3];
			this->field->field[ant->pos_x][ant->pos_y]->IDs[0] = num;
		}
	}
	if (ant->type == 1 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <=2) {
		 ant->aim = { rand() % 50+1,  rand() % 50+1 }; 
	}
	if (ant->type == 2 && dist(ant->pos_x, ant->pos_y, ant->aim.first, ant->aim.second) <= 2) {
		ant->aim = { rand() % 10 + 1,  rand() % 10 + 1 }; // коорды базы
		ant->action = 0;
	}

	if (ant->type == 3 && dist(ant->pos_x, ant->pos_y, ant->nearest_En.first, ant->nearest_En.first) <= 2) {
		ant->nearest_En = { rand() % 10 + 1,  rand() % 10 + 1 }; // коорды базы
		ant->action = 0;
	}


	

	if (ant->type == 1) {
		for (double i = -3; i <= 3; i++) {
			for (double j = -3; j <= 3; j++) {
				if (!(ant->pos_x + i < 0 or ant->pos_x + i >= field_size_x or ant->pos_y + j < 0 or ant->pos_y + j >= field_size_y)) {
					if (this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]) {
						Ant* smth = (Ant*)entityList[this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]]->getPtr();
						if (smth->type == 4) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->action = 1;
							
						}
						if (smth->type == 5) {
							ant->nearest_En = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->action = 1;
							cout << ant->action;
						}
						
						if ((smth->type == 2 or smth->type == 3) && ant->action == 1) {
							
							smth->nearest_En = ant->nearest_En;
							smth->nearest_Fd = ant->nearest_Fd;
							smth->aim = ant->nearest_Fd;
							smth->action = 1;
						}
					}
				}
			}
		}
	}


	if (ant->type == 2 or ant->type == 3) {
		for (double i = -1; i <= 1; i++) {
			for (double j = -1; j <= 1; j++) {
				if (!(ant->pos_x + i < 0 or ant->pos_x + i >= field_size_x or ant->pos_y + j < 0 or ant->pos_y + j >= field_size_y)) {
					if (this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]) {

						Ant* smth = (Ant*)entityList[this->field->field[(int)(ant->pos_x + i)][(int)(ant->pos_y + j)]->IDs[0]]->getPtr();
						if (smth->type == 4 && ant->type == 2) {
							ant->nearest_Fd = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->action = 1;
						}
						if (smth->type == 5 && ant->type == 3) {
							ant->nearest_En = { (int)(ant->pos_x + i),(int)(ant->pos_y + j) };
							ant->action = 1;
						}
						if (smth->type == 2 && ant->action == 1&& (dist(smth->pos_x, smth->pos_y, ant->nearest_Fd.first, ant->nearest_Fd.second) < dist(smth->pos_x, smth->pos_y, smth->nearest_Fd.first, smth->nearest_Fd.second))) {
							smth->nearest_En = ant->nearest_En;
							smth->nearest_Fd = ant->nearest_Fd;
							smth->aim = ant->nearest_Fd;
							smth->action = 1;
						}
					}
				}
			}
		}

	}

	
	
}


bool InfoSpace::DeleteEntity(unsigned int id) {
	Entity* curEnt = entityList[id];
	entityList.erase(id);
	if(curEnt->getType() == 1) {//еда
		
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