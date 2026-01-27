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
    std::vector<Level*> levels;
    Level* currentLevel;
    void bindLevelchangers(std::vector<Level*> levels);

  public:
    DungeonCrawler(AbstractView* ui) : ui(ui){
      buildLevels();
      currentLevel = levels.front();
    }
    Level* getCurrentLevel(){return currentLevel;}
    std::vector<Level*> buildLevels();
    void setCurrentLevel(Level* level){currentLevel = level;}
    std::vector<Level*> getLevels(){return levels;}
    bool turn();

};

#endif
