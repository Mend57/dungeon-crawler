#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include <iostream>

#include "AbstractView.h"
#include "GraphicalUI.h"
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
    bool turn();
};

#endif
