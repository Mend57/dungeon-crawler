#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include <iostream>

#include "AbstractView.h"
#include "GuardController.h"
#include "List.h"

class DungeonCrawler {
  private:
    AbstractView* ui;
    std::vector<Level*> levels;
    Level* currentLevel;

  public:
    DungeonCrawler(AbstractView* ui, std::vector<Level*> levels) : ui(ui), levels(levels), currentLevel(levels.front()) {}
    Level* getCurrentLevel(){return currentLevel;}
    void setCurrentLevel(Level* level){currentLevel = level;}

    bool turn(){
      for(Character* character : currentLevel->getCharacters()){
        Input input = character->getController()->move();
        if(input.getExit() == true) return false;
        character->setMoveDirection(input);

        Tile* currentTile = character->getTile();
        Tile* destTile = currentLevel->getTile(currentTile->getRow()+input.getDy(), currentTile->getColumn()+input.getDx());
        if (destTile->getTexture() == "E" && destTile != currentTile) {
          if (currentLevel == levels.at(0)) currentLevel = levels.at(levels.size()-1);
          else currentLevel = levels.at(0);
        }
        if (!currentTile->moveTo(destTile, character)) {
          if (GuardController* guardController = dynamic_cast<GuardController *>(character->getController())) guardController->decrementIndex();
        }
        for (Character* ch : currentLevel->getCharacters()) {
          if (ch->getHitpoints() <= 0) currentLevel->removeCharacter(ch);
        }
      }
      ui->draw(currentLevel);
      return true;
    }
};

#endif
