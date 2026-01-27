#include "DungeonCrawler.h"
#include "Tiles/Levelchanger.h"

bool DungeonCrawler::turn(){
    for (Character* character : currentLevel->getCharacters()) {
        Input input = character->getController()->move();
        if(input.getExit() == true) return false;
        character->setMoveDirection(input);
        Tile* currentTile = character->getTile();
        Tile* destTile = currentLevel->getTile(currentTile->getRow()+input.getDy(), currentTile->getColumn()+input.getDx());

        if (destTile->getTexture() == "E" && destTile != currentTile) {
            currentLevel = dynamic_cast<Levelchanger*>(dynamic_cast<Levelchanger*>(destTile)->getDestination())->getLevel();
            currentTile->moveTo(destTile, character);
            ui->drawLevel(currentLevel);
            ui->draw(currentLevel);
            break;
        }

        if (!currentTile->moveTo(destTile, character) && destTile->hasCharacter()) {
            if (GuardController* guardController = dynamic_cast<GuardController *>(character->getController())) guardController->decrementIndex();
        }

        for (Character* ch : currentLevel->getCharacters()) {
            if (!ch->isAlive()){
                ch->getTile()->setCharacter(nullptr);
                ch->clearLabel();
            }
        }
        ui->draw(currentLevel);
    }
    for (Character* ch : currentLevel->getCharacters()) {
        if (!ch->isAlive()) currentLevel->removeCharacter(ch);
    }
    bool mainCharactersAlive = false;
    for (Character* ch : currentLevel->getCharacters()) {
        if (ch->isCharacterPlayer()) mainCharactersAlive = true;
    }
    return mainCharactersAlive;
}
