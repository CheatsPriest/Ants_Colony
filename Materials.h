#pragma once
class Materials
{
public:
	int entity_id;
	int type;
	int pos_x;
	int pos_y;
	int pos_z;
	int weight;
	Materials(int x, int y, int z, int type, int weight) {
		this->pos_x = x;
		this->pos_y = y;
		this->pos_z = z;
		this->type = type;
		this->weight = weight;
	}
};

