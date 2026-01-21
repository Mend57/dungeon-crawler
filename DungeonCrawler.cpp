#include "DungeonCrawler.h"

bool DungeonCrawler::turn(){
    auto& characters = currentLevel->getCharacters();
    auto it = characters.begin();
    while (it != characters.end()) {
        Character* character = *it;
        for (auto jt = characters.begin(); jt != characters.end();) {
            if ((*jt)->getHitpoints() <= 0) jt = characters.erase(jt);
            ++jt;
        }

        Input input = character->getController()->move();
        if(input.getExit() == true) return false;
        character->setMoveDirection(input);

        Tile* currentTile = character->getTile();
        Tile* destTile = currentLevel->getTile(currentTile->getRow()+input.getDy(), currentTile->getColumn()+input.getDx());

        if (destTile->getTexture() == "E" && destTile != currentTile) {
            if (currentLevel == levels.at(0)) currentLevel = levels.at(levels.size()-1);
            else currentLevel = levels.at(0);
            currentTile->moveTo(destTile, character);
            ui->drawLevel(currentLevel);
            break;
        }

        if (!currentTile->moveTo(destTile, character)) {
            if (GuardController* guardController = dynamic_cast<GuardController *>(character->getController())) guardController->decrementIndex();
            if (destTile->hasCharacter()) ui->drawLevel(currentLevel);
        }
        for (Character* ch : currentLevel->getCharacters()) {
            if (ch->getHitpoints() <= 0) currentLevel->removeCharacter(ch);
        }

        ++it;
    }
    ui->draw(currentLevel);
    return true;
}