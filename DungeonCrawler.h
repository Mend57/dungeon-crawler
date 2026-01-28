#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include <iostream>

#include "AbstractView.h"
#include "GraphicalUI.h"
#include "GuardController.h"
#include "StationaryController.h"
#include "List.h"

class DungeonCrawler {
  private:
    AbstractView* ui;
    List<Level*> levels;
    Level* currentLevel;
    void bindLevelchangers(List<Level*>& levels);
    void buildLevels();

  public:
    DungeonCrawler(AbstractView* ui) : ui(ui){
      buildLevels();
      currentLevel = levels.front();
    }
    Level* getCurrentLevel(){return currentLevel;}
    void setCurrentLevel(Level* level){currentLevel = level;}
    List<Level*> getLevels(){return levels;}
    bool turn();
};

#endif
