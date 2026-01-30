#ifndef CHARACTER_H
#define CHARACTER_H
#include "controllers/AbstractController.h"
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
      Character(Tile* tile, AbstractController* controller, const int strength, const int stamina) : tile(tile), controller(controller), strength(strength), stamina(stamina){
          setLabel();
          hitpoints = getMaxHP();
      }
      virtual ~Character() = default;
      Tile* getTile() const {return tile;}
      void setTile(Tile* tile){this->tile = tile;}
      void setMoveDirection(Input input){moveDirection = input;}
      AbstractController* getController() const {return controller;}
      void setLabel() const;
      void clearLabel() const {label->clear();}
      void setHitpoints(const int hitpoints){this->hitpoints = hitpoints;}
      bool isCharacterPlayer() const {return this->isPlayer;}
      QLabel* getLabel() const {return label;}
      int getMaxHP() const{return 20+(stamina*5);}
      int getStrength() const{return strength;}
      int getStamina() const{return stamina;}
      int getHitpoints() const{return hitpoints;}
      bool isAlive() const{return alive;}
      void die(){alive = false;}
      void setController(AbstractController* controller){this->controller = controller;}
      void isMainCharacter(){
          this->isPlayer = true;
          setLabel();
      }
};

#endif
