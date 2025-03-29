#include "Food.h"

void Food::CopyPosition(Ant* hauler) {
    pos_x = hauler->pos_x;
    pos_y = hauler->pos_y;
    pos_z = hauler->pos_z;
}