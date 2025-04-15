#pragma once
#include "Entity.h"
#include <map>
#include "Field.h"

#include "Collector.h"
#include "Stockpile.h"
#include "Colony.h"


class InfoSpace
{
public:

	bool mainLoop = true;

	int x_cam, y_cam, z_cam;
	int cam_speed;

	int main_window_wide;
	int main_window_hight;

	int field_size_x;
	int field_size_y;
	int cell_size;

	unsigned int free_key;
	unsigned int free_stockpile_key;

	Field* field;

	map<unsigned int, Entity*> entityList;

	map<unsigned int, Stockpile*> stockpileList;
	map<int, Colony*> coloniesList;

	bool draw_debug_move_lines;

	
	InfoSpace() {


		cam_speed = 4;

		x_cam = 1000 * cam_speed;
		y_cam = 1000 * cam_speed;
		z_cam = 0;

		
		cell_size = cam_speed;

		main_window_wide = 1000;
		main_window_hight = 1000;

		field_size_x = size_x;
		field_size_y = size_y;

		free_key = 1;
		free_stockpile_key = 1;

		field = new Field;

		draw_debug_move_lines = false;
	}

	//type - 1 = муравей; under_class: 1 = Scout, 2 = Worker, 3 = Soldier, 0 = Queen
	bool CreateEntityAnt(int x, int y, int z, int type, int under_class, int clan);
	bool CreateEntityFood(int x, int y, int z, int type, float food_value, int weight);
	bool CreateEntity(int x, int y, int t); // костыль дениса
	bool CreateStockpile(int x, int y, int z, int wide, int hight, int type, int clan);
	bool CreateEntityMaterial(int x, int y, int z, int type, int weight);

	bool isValidCell(pair<int, int> d);
	bool CreateInsect(int x, int y, int z, InsectTypes type, pair<int, int> stockPos, pair<int, int> stockSize, bool isSlaver);
	bool isFreeCell(pair<int, int>p);


	bool BuildWall(Ant* cAnt);

	pair<int, int> searchmat();
	

	bool DeleteEntity(unsigned int id);
	void MoveCam(int x, int y);
	void MoveEntity(unsigned int id);
	void ProcessAnt(Ant* curAnt);
	void moveToCeil(pair<int, int> newPos2, unsigned int id, Insect* ent);
	void RandomMove(pair<int, int> newPos2, unsigned int id, Insect* curr);
	void MoveInsect(unsigned int id);
	void MoveAphid(unsigned int id, Insect* insect);
	pair<bool, Stockpile*> IndoorsStockpile(pair<int, int> p);
	void MoveLadybug(unsigned int id, Insect* insect);
	void attack(int atkr, int defr);
	bool BornNewAnts(Ant* Queen);
	bool FeedTheQueen(Ant* curAnt);
	bool CreateEntityMaggot(int x, int y, int z, int clan);
	void Hatching(Stockpile* curStock);
	bool ChangeEntityPosition(unsigned int ind, int x, int y, int z);
	bool TryToDrop(pair<int, int> stockPos, int id);
	bool TryToDrop(Ant* ant);
	bool Picked(unsigned int ind);

	void spawnEat(pair<int, int> position) {
		double chaince = 0.001;
		if ( ((double)(rand() % 10000) / 10000) <= chaince) {
			cout << (rand() % 10000) / 10000 << "\n";
			CreateEntityFood(position.first, position.second, 0, 0, 2000, 10);
		}
	}

	void ReCalculateTheColony();
	void BuildNewStockpile(Colony* curColony);
	void RecountAphid();

	~InfoSpace() {
		delete field;
	}
};

