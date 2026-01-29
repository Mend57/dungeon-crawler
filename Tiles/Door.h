#ifndef DUNGEONCRAWLER_DOOR_H
#define DUNGEONCRAWLER_DOOR_H
#include "../Passive.h"
#include "Floor.h"
#include "Wall.h"

class Door : public Floor, public Wall, public Passive {
  private:
    bool isDoorOpen;
    Level* level;
    std::vector<Tile*> adjacentTiles;

  public:
    Door(const int row, const int column, Level* level) : Tile(row, column, "X"), Floor(row,column), Wall(row,column), level(level), isDoorOpen(false){Tile::setLabel();}
    bool isOpen() const {return isDoorOpen;}
    void addAdjacent(Tile* tile) {adjacentTiles.push_back(tile);}
    std::pair<bool, Tile*> onEnter(Character* who) override {return isDoorOpen ? Floor::onEnter(who) :  Wall::onEnter(who);}
    void notify() override {
      isDoorOpen = !isDoorOpen;
      setTexture(isDoorOpen ? "/" : "X");
      Tile::setLabel();
      if (isDoorOpen) {
        setWalkable(true);
        // Quando a porta abre, conecta todos os tiles adjacentes entre si
        for (size_t i = 0; i < adjacentTiles.size(); i++) {
          for (size_t j = i + 1; j < adjacentTiles.size(); j++) {
            if (adjacentTiles[i] && adjacentTiles[j]) {
              level->addEdge(adjacentTiles[i], adjacentTiles[j]);
            }
          }
          // Também conecta a porta aos tiles adjacentes
          level->addEdge(this, adjacentTiles[i]);
        }
      } else {
        setWalkable(false);
        // Quando a porta fecha, remove todas as conexões
        for (size_t i = 0; i < adjacentTiles.size(); i++) {
          for (size_t j = i + 1; j < adjacentTiles.size(); j++) {
            if (adjacentTiles[i] && adjacentTiles[j]) {
              level->removeEdge(adjacentTiles[i], adjacentTiles[j]);
            }
          }
          level->removeEdge(this, adjacentTiles[i]);
        }
      }
    }

};

#endif