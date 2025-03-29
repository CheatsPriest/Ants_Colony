#pragma once

#include <map>
#include "Field.h"
#include "Entity.h"
#include "Collector.h"
#include "Stockpile.h"

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


	bool draw_debug_move_lines;

	InfoSpace() {

		

		x_cam = 0;
		y_cam = 0;
		z_cam = 0;

		cam_speed = 5;
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
	bool CreateEntityAnt(int x, int y, int z, int type, int under_class);
	bool CreateEntityFood(int x, int y, int z, int type, float food_value, int weight);
	bool CreateEntity(int x, int y, int t); // костыль дениса
	bool CreateStockpile(int x, int y, int z, int wide, int hight);


	bool DeleteEntity(unsigned int id);
	void MoveCam(int x, int y);
	void MoveEntity(unsigned int id);
	void ProcessAnt(Ant* curAnt);

	~InfoSpace() {
		delete field;
	}
};

