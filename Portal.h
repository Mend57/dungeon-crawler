#ifndef PORTAL_H
#define PORTAL_H
#include "Tile.h"


class Portal : public Tile {
    private:
      Tile* destination;

    public:
      Portal(const int row, const int column, Tile* destination) : Tile(row, column, "O"), destination(destination){}
      Tile* getDestination(){return destination;}
      void setDestination(Tile* destination) {
          this->destination = destination;
      }
      void setLabel() override {
          std::string floorTexture = GraphicalUI::.at(rand() % .size());
          label->setPixmap(GraphicalUI::getFloorTexture(floorTexture));
      }
      std::pair<bool, Tile*> onEnter(Character* who) override {return {!(destination->hasCharacter()), destination};}
};



#endif
