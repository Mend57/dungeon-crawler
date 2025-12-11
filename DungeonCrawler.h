#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "AbstractView.h"

class DungeonCrawler {
  private:
    AbstractView* abstractView;
    Level* level;

  public:
    DungeonCrawler(AbstractView* abstractView, Level* level) : abstractView(abstractView), level(level) {}

    bool turn(){
      for(Character* character : level->getCharacters()){
        Input input = character->getController()->move();
        if(input.getExit() == true) return false;

        Tile* currentTile = character->getTile();
        Tile* destTile = level->getTile(currentTile->getRow()+input.getDy(), currentTile->getColumn()+input.getDx());
        currentTile->moveTo(destTile, character);

        abstractView->draw(level);
        return true;
      }
    }
};

#endif
