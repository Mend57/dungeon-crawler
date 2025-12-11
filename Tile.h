#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <utility>
#include <QLabel>
#include "Character.h"
#include "GraphicalUI.h"

class Tile {
  private:
    Character* character;
    const int row;
    const int column;
    std::string texture;

  protected:
    QLabel* label;
    Tile(const int row, const int column, std::string texture) : character(nullptr), row(row), column(column), texture(std::move(texture)) {
      Tile::setLabel();
    }

  public:
    virtual ~Tile() = default;
    std::string getTexture(){return texture;}
    Character* getCharacter(){return character;}
    int getRow() const{return row;}
    int getColumn() const{return column;}
    void setCharacter(Character* character){this->character = character;}
    void setTexture(std::string texture) {
      this->texture = std::move(texture);
    }
    bool hasCharacter(){return character != nullptr;}
    QLabel* getLabel() {return label;}
    virtual void setLabel() {
      QPixmap label = GraphicalUI::getLabelFromString(std::move(texture));
      this->label->setPixmap(label);
    }

    virtual std::pair<bool, Tile*> onEnter(Character* who) = 0;
    virtual bool onLeave(Tile* destTile, Character* who);
    bool moveTo(Tile* destTile, Character* who);
};



#endif
