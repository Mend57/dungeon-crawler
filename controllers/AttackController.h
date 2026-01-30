#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H
#include "../Level.h"

class AttackController : public AbstractController {
  private:
    Level* level;
    Character* target;
    Tile* tile;
    int pauseCounter = 0;

  public:
    AttackController(Level* level, Tile* tile) : level(level), tile(tile) {
      const std::vector<Character*> mainCharacters = level->getMainCharacters();
      target = mainCharacters.at(rand() % mainCharacters.size());
    }
    void setTile(Tile* tile) {this->tile = tile;}
    Input move() override {
      if (pauseCounter >= 5){
        pauseCounter = 0;
        return {0,0};
      }
      Tile* targetTile = target->getTile();
      std::vector<Tile*> path = level->getPath(tile, targetTile);
      if (path.size() < 2) return {0,0};
      const Tile* nextTile = path[1];
      int dr = nextTile->getRow() - tile->getRow();
      int dc = nextTile->getColumn() - tile->getColumn();
      if ((dr >= -1 && dr <= 1) && (dc >= -1 && dc <= 1)){
        pauseCounter++;
        return {dc, dr};
      }
      return {0,0};
    }};

#endif
