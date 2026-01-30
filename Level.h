#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <vector>
#include "AbstractView.h"
#include "tiles/Tile.h"
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
      struct Node {
        int row;
        int col;
        int dist = INT_MAX;
        bool visited = false;
        Node* prev = nullptr;
      };
      std::vector<Node*> nodes;
      std::unordered_map<Node*, std::vector<Node*>> graph;

    public:
      Level(int height, int width, AbstractController* ui, std::string map, const std::string& filename);
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
      std::vector<Tile*> getPath(const Tile* from, const Tile* to);
      void addEdge(const Tile* tile1, const Tile* tile2);
      void removeEdge(const Tile* tile1, const Tile* tile2);
      Node* getNode(const int row, const int col) {
        for (Node* node : nodes) {
          if (node->row == row && node->col == col){
            return node;
          }
        }
        return nullptr;
      }

      std::vector<Node*> getNeighbors(Node* node) {
        static const std::vector<Node*> empty;
        const auto it = graph.find(node);
        return (it != graph.end()) ? it->second : empty;
      }
};

#endif
