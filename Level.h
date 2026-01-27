#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Tiles/Tile.h"
#include "Character.h"

class Level {
    private:
      std::vector<std::vector<Tile*>> tileMap;
      std::vector<Character*> characters;
      std::vector<Character*> mainCharacters;
      const int height;
      const int width;
      std::vector<Tile*> levelchangers;
      std::string l;

    public:
      Level(int height, int width, AbstractController* ui, std::string levelDesign);
      ~Level();
      int getHeight() const{return height;}
      int getWidth() const{return width;}
      std::vector<Tile*> getLevelchangers(){return levelchangers;}
      std::vector<std::vector<Tile*>> getTileMap(){return tileMap;}
      std::vector<Character*>& getCharacters(){return characters;}
      std::vector<Character*> getMainCharacters(){return mainCharacters;}
      void setMainCharacter(Character* character);
      Tile* getTile(int row, int column);
      const Tile* getTile(int row, int col) const;
      void placeCharacter(Character *c, int row, int col);
      void addCharacter(Character* character);
      void removeCharacter(Character* character);
};

#endif
