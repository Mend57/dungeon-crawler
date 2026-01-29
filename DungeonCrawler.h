#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include <fstream>
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
    void bindLevelchangers(Level* level);
    void addCharacters(Level* level);

  public:
    DungeonCrawler(AbstractView* ui, bool newGame);
    Level* getCurrentLevel(){return currentLevel;}
    void setCurrentLevel(Level* level){currentLevel = level;}
    std::vector<Level*> getLevels(){return levels;}
    bool turn();
    void saveGame();
    void buildLevels(QDir dir);
};

#endif
