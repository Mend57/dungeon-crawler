#ifndef TERMINALUI_H
#define TERMINALUI_H
#include "AbstractController.h"
#include "AbstractView.h"
#include <iostream>
#include <set>
#include "DungeonCrawler.h"

class TerminalUI: public AbstractView, public AbstractController {
  private:
    DungeonCrawler* dungeonCrawler;

  public:
    TerminalUI() : dungeonCrawler(new DungeonCrawler(this)) {dungeonCrawler->buildLevels();}
    void draw(Level* level) override;
    void drawLevel(Level* level) override{};
    Input move() override;
};

#endif
