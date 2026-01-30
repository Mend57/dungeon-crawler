#ifndef TILE_H
#define TILE_H
#include <QLabel>
#include "../Character.h"

class Tile {
  private:
    Character* character;
    const int row;
    const int column;
    std::string texture;
    bool walkable = true;

  protected:
    QLabel* label = new QLabel();

    Tile(const int row, const int column, std::string texture) : character(nullptr), row(row), column(column), texture(std::move(texture)) {
      Tile::setLabel();
    }

  public:
    virtual ~Tile() = default;
    virtual void setLabel();
    virtual std::pair<bool, Tile*> onEnter(Character* who) = 0;
    virtual bool onLeave(Tile* destTile, Character* who);
    std::string getTexture(){return texture;}
    Character* getCharacter() const {return character;}
    int getRow() const{return row;}
    int getColumn() const{return column;}
    void setCharacter(Character* character){this->character = character;}
    void setTexture(std::string texture) {this->texture = std::move(texture);}
    bool hasCharacter() const {return character != nullptr;}
    QLabel* getLabel() const {return label;}
    bool moveTo(Tile* destTile, Character* who);
    bool isWalkable() const{return walkable;}
    void setWalkable(const bool walkable){this->walkable = walkable;}
};



#endif
