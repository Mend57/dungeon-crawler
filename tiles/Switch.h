#ifndef DUNGEONCRAWLER_SWITCH_H
#define DUNGEONCRAWLER_SWITCH_H
#include "../Active.h"
#include "Floor.h"

class Switch : public Floor, public Active {
  public:
    Switch(const int row, const int column) : Tile(row, column, "?"), Floor(row, column){}
    std::pair<bool, Tile*> onEnter(Character* who) override {
        activate();
        return Floor::onEnter(who);
    }

};
#endif