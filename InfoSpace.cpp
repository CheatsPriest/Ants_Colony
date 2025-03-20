#include "InfoSpace.h"


//type - 1 = муравей; under_class: 1 = Scout, 2 = Worker, 3 = Soldier, 0 = Queen
bool InfoSpace::CreateEntity(int x, int y, int z, int type, int under_class) {
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

void InfoSpace::MoveCam(int x_d, int y_d) {
	x_cam += x_d*cam_speed;
	y_cam += y_d*cam_speed;
	if (x_cam < 0)x_cam = 0;
	else if (x_cam > field_size_x*cell_size - main_window_wide)x_cam =x_cam-cam_speed;
	if (y_cam < 0)y_cam = 0;
	else if (y_cam > field_size_y*cell_size - main_window_hight)y_cam = y_cam-cam_speed;
}