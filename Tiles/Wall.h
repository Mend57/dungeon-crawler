#ifndef WALL_H
#define WALL_H
#include "Tile.h"

class Wall : public virtual Tile {
    public:
      Wall(const int row, const int column) : Tile(row, column, "#"){};
      std::pair<bool, Tile*> onEnter(Character* who) override {return {false, nullptr};}
};

#endif
