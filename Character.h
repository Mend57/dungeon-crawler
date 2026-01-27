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
      int strength;
      int stamina;
      int hitpoints;
      bool isPlayer = false;
      bool alive = true;

    public:
      Character(Tile* tile, AbstractController* controller, int strength, int stamina) : tile(tile), controller(controller), strength(strength), stamina(stamina){
          setLabel();
          hitpoints = getMaxHP();
      }
      virtual ~Character() = default;
      Tile* getTile(){return tile;}
      void setTile(Tile* tile){this->tile = tile;}
      void setMoveDirection(Input input){moveDirection = input;}
      AbstractController* getController(){return controller;}
      void setLabel();
      void clearLabel(){label->clear();}
      void setHitpoints(int hitpoints){this->hitpoints = hitpoints;}
      bool isCharacterPlayer() {return this->isPlayer;}
      QLabel* getLabel(){return label;}
      int getMaxHP(){return 20+(stamina*5);}
      int getStrength(){return strength;}
      int getStamina(){return stamina;}
      int getHitpoints(){return hitpoints;}
      bool isAlive(){return alive;}
      void die(){alive = false;}
      void isMainCharacter(){
          this->isPlayer = true;
          setLabel();
      }
};

#endif
