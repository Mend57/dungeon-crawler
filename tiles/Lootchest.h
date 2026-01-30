#ifndef LOOTCHEST_H
#define LOOTCHEST_H
#include "Floor.h"

class Lootchest : public Floor {
    public:
        Lootchest(const int row, const int column) : Tile(row, column, "V"), Floor(row, column){}
};

#endif
