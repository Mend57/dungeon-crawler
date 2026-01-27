#ifndef DUNGEONCRAWLER_ABSTRACTUI_H
#define DUNGEONCRAWLER_ABSTRACTUI_H
#include "Level.h"

class Level;

class AbstractView {
  public:
    virtual void draw(Level* level) = 0;
    virtual void drawLevel(Level* level) = 0;
    virtual ~AbstractView() = default;
};

#endif