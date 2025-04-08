#include "Ant.h"
#include <algorithm>
#include "InfoSpace.h"

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
    this->saturation = max_Saturation;
    this->aim = { this->pos_x,this->pos_y };
    nearest_En = { this->pos_x,this->pos_y };
    nearest_Mat = { this->pos_x,this->pos_y };
    nearest_Fd = { this->pos_x,this->pos_y };
    inventary = 0;
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
bool Ant::Take(unsigned int taked_id) {

    if (inventary != 0)return false;
    inventary = taked_id;
    return true;
}
//Копировать позицию в текущего
void Ant::CopyPosition(Ant* source) {
    pos_x = source->pos_x;
    pos_y = source->pos_y;
    pos_z = source->pos_z;
}
//Копировать позицию из текущего
void Ant::GivePosition(Ant* input) {
    input->pos_x = pos_x;
    input->pos_y = pos_y;
    input->pos_z = pos_z;
}
unsigned int Ant::Put() {
    unsigned int out = 0;
    out = inventary;
    inventary = 0;
    return out;
}
void InfoSpace::ProcessAnt(Ant* curAnt) {
    if (curAnt->type == 1) {//scout

    }
    else if (curAnt->type == 2) {//worker
        if (curAnt->action == 1) {

        }
    }
    else if (curAnt->type == 3) {//soldier

    }
}