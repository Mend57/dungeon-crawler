#ifndef DUNGEONCRAWLER_DOOR_H
#define DUNGEONCRAWLER_DOOR_H
#include "../Passive.h"
#include "Floor.h"
#include "Wall.h"

class Door : public Floor, public Wall, public Passive {
  private:
    bool isDoorOpen;

  public:
    Door(const int row, const int column) : Tile(row, column, "X"), Floor(row,column), Wall(row,column), isDoorOpen(false){Tile::setLabel();}
    bool isOpen() const {return isDoorOpen;}
    std::pair<bool, Tile*> onEnter(Character* who) override {return isDoorOpen ? Floor::onEnter(who) :  Wall::onEnter(who);}
    void notify() override {
      isDoorOpen = !isDoorOpen;
      setTexture(isDoorOpen ? "/" : "X");
      Tile::setLabel();
    }
};

#endif