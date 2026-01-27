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
            if (GuardController* guardController = dynamic_cast<GuardController*>(character->getController())) guardController->decrementIndex();
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

std::vector<Level*> DungeonCrawler::buildLevels(){
    AbstractController* controller = dynamic_cast<AbstractController*>(ui);
    Level* level1 = new Level(10, 10, controller, {
          "##########"
          "#O.......#"
          "#...<....#"
          "#..___...#"
          "#..___...#"
          "#........#"
          "#######X##"
          "#O......E#"
          "#...?....#"
          "##########"
    });

    Level* level2 = new Level(10, 10, controller, {
          "##########"
          "#.O......#"
          "#....<...#"
          "#...__...#"
          "#........#"
          "#........#"
          "#######X##"
          "#O....E.E#"
          "#...?....#"
          "##########"
      });

    Level* level3 = new Level(10, 10, controller, {
          "##########"
          "#.O......#"
          "#....<...#"
          "#...__...#"
          "#........#"
          "#........#"
          "#######X##"
          "#O......E#"
          "#...?...V#"
          "##########"
      });

    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);

    bindLevelchangers(levels);

    std::vector<Character*> mainCharacters;
    Character* mainCharacter1 = new Character(level1->getTile(2,3), controller, 10, 10);
    mainCharacters.push_back(mainCharacter1);
    level1->placeCharacter(mainCharacter1,2,3);

    for (Level* level : levels) {
        for (Character* mc : mainCharacters) level->setMainCharacter(mc);
    }

    Character* stationary = new Character(level1->getTile(2,3), new StationaryController(), 10, 10);
    Character* guard1 = new Character(level1->getTile(2,3), new GuardController(), 5, 5);
    Character* guard2 = new Character(level1->getTile(2,3), new GuardController(), 5, 5);
    level1->placeCharacter(stationary,3,1);
    level1->placeCharacter(guard1,5,5);
    level1->placeCharacter(guard2,7,5);
    return levels;
}

void DungeonCrawler::bindLevelchangers(std::vector<Level*> levels) {
    for (size_t i = 0; i + 1 < levels.size(); ++i) {
        Levelchanger* lc1 = nullptr;
        Levelchanger* lc2 = nullptr;
        for (Tile* levelchanger : levels.at(i)->getLevelchangers()) {
            Levelchanger* lc = dynamic_cast<Levelchanger*>(levelchanger);
            if (lc->getDestination() == nullptr) {
                lc1 = lc;
                break;
            }
        }
        for (Tile* levelchanger : levels.at(i+1)->getLevelchangers()) {
            Levelchanger* lc = dynamic_cast<Levelchanger*>(levelchanger);
            if (lc->getDestination() == nullptr) {
                lc2 = lc;
                break;
            }
        }
        lc1->setDestination(lc2);
        lc2->setDestination(lc1);
    }
}
