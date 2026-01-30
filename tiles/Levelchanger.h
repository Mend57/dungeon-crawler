#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H

#include "Portal.h"

class Levelchanger : public Portal {
  private:
    Level* level;

  public:
    Levelchanger (const int row, const int column, Level* level) : Tile(row, column, "E"), Portal(row, column), level(level){};
    Level* getLevel() const {return level;}
};

#endif
