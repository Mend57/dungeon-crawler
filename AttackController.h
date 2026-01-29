#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include "Level.h"

class AttackController : public AbstractController {
  private:
    Level* level;
    Character* target;
    Tile* tile;
    int pauseCounter = 0;
    Input left = {-1,0};
    Input right = {1,0};
    Input up = {0,-1};
    Input down = {0,1};
    Input upLeft = {-1,-1};
    Input upRight = {1,-1};
    Input downLeft = {-1,1};
    Input downRight = {1,1};

  public:
    AttackController(Level* level, Tile* tile) : level(level), tile(tile) {
      std::vector<Character*> mainCharacters = level->getMainCharacters();
      target = mainCharacters.at(rand() % mainCharacters.size());
    }
    void setTile(Tile* tile) {this->tile = tile;}
    Input move() override {
      Tile* targetTile = target->getTile();
      std::vector<Tile*> path = level->getPath(tile, targetTile);
      if (path.size() < 2) return {0,0};
      Tile* nextTile = path[1];
      int dr = nextTile->getRow() - tile->getRow();
      int dc = nextTile->getColumn() - tile->getColumn();
      if (dr == -1 && dc == 0) return up;
      if (dr == 1 && dc == 0) return down;
      if (dr == 0 && dc == -1) return left;
      if (dr == 0 && dc == 1) return right;
      if (dr == -1 && dc == -1) return upLeft;
      if (dr == -1 && dc == 1) return upRight;
      if (dr == 1 && dc == -1) return downLeft;
      if (dr == 1 && dc == 1) return downRight;
      return {0,0};
    }};

#endif
