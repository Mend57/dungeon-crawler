#ifndef DUNGEONCRAWLER_PIT_H
#define DUNGEONCRAWLER_PIT_H
#include "Floor.h"

class Pit : public Floor {
    public:
        Pit(const int row, const int column) : Tile(row, column, "_"), Floor(row, column){}
        bool onLeave(Tile* destTile, Character* who) override{return (destTile->getTexture() == "<" || destTile->getTexture() == "_") ? Tile::onLeave(destTile, who) : false;}

};

#endif