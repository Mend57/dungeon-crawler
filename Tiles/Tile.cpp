#include "Tile.h"
#include "../GraphicalUI.h"

bool Tile::onLeave(Tile* destTile, Character* who){
  if (!hasCharacter() || character != who || destTile == nullptr || destTile->hasCharacter()) return false;
  return true;
}

bool Tile::moveTo(Tile* destTile, Character* who){
  if(onLeave(destTile, who) == false) return false;
  std::pair<bool, Tile*> tileEntered = destTile->onEnter(who);
  if(tileEntered.first == false) return false;
  Tile* destinationTile = tileEntered.second != nullptr ? tileEntered.second : destTile;

  this->character = nullptr;
  (destinationTile)->character = who;
  who->setTile(destinationTile);
  who->setLabel();
  return true;
}

void Tile::setLabel() {
  this->label->setPixmap(GraphicalUI::getLabelFromString(texture));
}

