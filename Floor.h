#ifndef FLOOR_H
#define FLOOR_H
#include "GraphicalUI.h"
#include "Tile.h"

class Floor : public virtual Tile{
private:
    std::vector<std::string> floorTextures = {"floor1, floor2, floor3, floor4, floor5"};

public:
    Floor(const int row, const int column) : Tile(row, column, "."){}
    std::pair<bool, Tile*> onEnter(Character* who) override{return {true, nullptr};}
    void setLabel() override {label->setPixmap(GraphicalUI::getFloorTexture(floorTextures.at(rand() % floorTextures.size())));}
};

#endif
