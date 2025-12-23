#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "AbstractView.h"

class DungeonCrawler {
  private:
    AbstractView* ui;
    Level* level;

  public:
    DungeonCrawler(AbstractView* ui, Level* level) : ui(ui), level(level) {}

    bool turn(){
      for(Character* character : level->getCharacters()){
        Input input = character->getController()->move();
        if(input.getExit() == true) return false;

        Tile* currentTile = character->getTile();
        Tile* destTile = level->getTile(currentTile->getRow()+input.getDy(), currentTile->getColumn()+input.getDx());
        currentTile->moveTo(destTile, character);

        ui->draw(level);
        return true;
      }
    }
};

#endif
