#include "Ant.h"
#include <algorithm>


Ant::Ant(int x, int y,int z, int type, float max_HP, int smell_Rad, float defense, float max_Saturation) : Ant() 
{
    this->pos_x = x;
    this->pos_y = y;
    this->pos_z = z;
    this->type = type;
    this->max_HP = max_HP;
    this->smell_Rad = smell_Rad;
    this->defense = defense;
    this->max_Saturation = max_Saturation;
    this->aim = { this->pos_x,this->pos_y };
    nearest_En = { this->pos_x,this->pos_y };
    nearest_Fd = { this->pos_x,this->pos_y };
}

bool Ant::isAlive()
{
    return false;
}

void Ant::Eat(int id_food_in_entity)
{
//        Food* food = (Food*)InfoSpace::entityList[id_food_in_entity];
//float remains = max_Saturation - saturation;
//if (food->food_value >= remains) {
//    saturation = max_Saturation;
//    food->food_value -= remains;
//}
//else {
//    saturation += food->food_value;
//   food->food_value = 0;
//}
//if (food->food_value <= 0) {
//    InfoSpace::entityList.erase(food->entity_id);
//}
}


