#pragma once

#include <map>
#include "Field.h"
#include "Entity.h"

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

	Field* field;
	map<unsigned int, Entity*> entityList;
	InfoSpace() {
		x_cam = 0;
		y_cam = 0;
		z_cam = 0;

		cam_speed = 20;
		cell_size = cam_speed;

		main_window_wide = 800;
		main_window_hight = 800;

		field_size_x = size_x;
		field_size_y = size_y;

		field = new Field;

	}
	~InfoSpace() {
		delete field;
	}
};

