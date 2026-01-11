#ifndef CHARACTER_H
#define CHARACTER_H
#include "AbstractController.h"
#include <QLabel>

class Tile;

class Character {
    private:
      Tile* tile;
      AbstractController* controller;
      QLabel* label = new QLabel();
      Input moveDirection = {0, 0};

    public:
      Character(Tile* tile, AbstractController* controller) : tile(tile), controller(controller) {setLabel();}
      virtual ~Character() = default;
      Tile* getTile(){return tile;}
      void setTile(Tile* tile){this->tile = tile;}
      void setMoveDirection(Input input){moveDirection = input;}
      AbstractController* getController(){return controller;}
      void setLabel();
      QLabel* getLabel(){return label;}
};

#endif
