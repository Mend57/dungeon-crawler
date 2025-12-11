#ifndef PORTAL_H
#define PORTAL_H
#include "Tile.h"


class Portal : public Tile {
    private:
      Tile* destination;
      std::vector<std::string> portalTextures = {"portal1, portal2, portal3"};

    public:
      Portal(const int row, const int column, Tile* destination) : Tile(row, column, "O"), destination(destination){}
      Tile* getDestination(){return destination;}
      void setDestination(Tile* destination) {this->destination = destination;}
      void setLabel(int textureIndex) {label->setPixmap(GraphicalUI::getPortalTexture(portalTextures.at(textureIndex)));}
      std::pair<bool, Tile*> onEnter(Character* who) override {return {!(destination->hasCharacter()), destination};}
};



#endif
