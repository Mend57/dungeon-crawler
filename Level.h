#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Tiles/Tile.h"
#include "Character.h"

class Level {
    private:
      std::vector<std::vector<Tile*>> tileMap;
      std::vector<Character*> characters;
      Character* mainCharacter;
      const int height;
      const int width;
      std::string l;

    public:
      Level(int height, int width, AbstractController* ui, std::string levelDesign);
      ~Level();
      int getHeight() const{return height;}
      int getWidth() const{return width;}
      std::vector<std::vector<Tile*>> getTileMap(){return tileMap;}
      std::vector<Character*> getCharacters(){return characters;}
      Character* getMainCharacter(){return mainCharacter;}
      void setMainCharacter(Character* character);
      Tile* getTile(int row, int column);
      const Tile* getTile(int row, int col) const;
      void placeCharacter(Character *c, int row, int col);
      void addCharacter(Character* character);
      void removeCharacter(Character* character);
};

#endif
