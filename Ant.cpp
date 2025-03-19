#include "Ant.h"

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
}

bool Ant::isAlive()
{
    return false;
}

void Ant::Eat()
{
}

void Ant::Move(int pos_X, int pos_Y, int smell_Rad)
{
}

