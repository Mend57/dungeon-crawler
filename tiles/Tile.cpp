#include "Tile.h"
#include "../GraphicalUI.h"

bool Tile::onLeave(Tile* destTile, Character* who){
  if (destTile == nullptr || !who->isAlive()) return false;
  if (destTile->hasCharacter() && (destTile->getCharacter()->isCharacterPlayer() ^ who->isCharacterPlayer())) {
      Character* defender = destTile->getCharacter();
      defender->setHitpoints(defender->getHitpoints() - who->getStrength());
      if (defender->getHitpoints() <= 0) {
        defender->die();
        return false;
      }
      who->setHitpoints(who->getHitpoints() - defender->getStrength());
      if (who->getHitpoints() <= 0) who->die();
  }
  if (!hasCharacter() || destTile->hasCharacter()) return false;
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

