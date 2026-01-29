#ifndef LEVEL_H
#define LEVEL_H
#include <vector>

#include "AbstractView.h"
#include "Tiles/Tile.h"
#include "Character.h"

class Level {
    private:
      std::vector<std::vector<Tile*>> tileMap;
      std::vector<Character*> characters;
      std::vector<Character*> mainCharacters;
      const int height;
      const int width;
      AbstractController* ui;
      std::string map;
      std::string filename;
      void bindPortals(std::ifstream& in, std::string& line);
      void buildCharacters(std::ifstream& in, std::string& line);
      void bindSwitches(std::ifstream& in, std::string& line);
      void openDoors(std::ifstream& in, std::string& line);

    public:
      Level(int height, int width, AbstractController* ui, std::string map, std::string filename);
      ~Level();
      int getHeight() const{return height;}
      int getWidth() const{return width;}
      std::vector<std::vector<Tile*>> getTileMap(){return tileMap;}
      std::vector<Character*>& getCharacters(){return characters;}
      std::vector<Character*> getMainCharacters(){return mainCharacters;}
      void setMainCharacter(Character* character);
      Tile* getTile(int row, int column);
      const Tile* getTile(int row, int col) const;
      void placeCharacter(Character *c, int row, int col);
      void addCharacter(Character* character);
      void removeCharacter(Character* character);
      static Level* CSVLoader(AbstractController* ui, const std::string& filename);
      static std::vector<std::string> splitLine(const std::string& line, char delimiter = ',');
      std::string getFilename() {return filename;}
};

#endif
