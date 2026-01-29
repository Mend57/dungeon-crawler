#include "DungeonCrawler.h"

#include "AttackController.h"
#include "Tiles/Door.h"
#include "Tiles/Levelchanger.h"

DungeonCrawler::DungeonCrawler(AbstractView* ui, bool newGame) : ui(ui){
    buildLevels(newGame ? QDir("../Levels") : QDir("../Save"));
    if (newGame) {
        currentLevel = levels.front();
        for (Level* level : levels) {
            for (Character* character : level->getCharacters()) character->setHitpoints(character->getMaxHP());
            if (level != levels.front()) {
                for (Character* mc : levels.front()->getMainCharacters()) level->setMainCharacter(mc);
            }
        }
    }
    else {
        std::ifstream in("../Save/State.csv");
        std::string line;
        std::getline(in, line);
        if (line == "#LOCATION") {
            std::getline(in, line);
            std::vector<std::string> tokens = Level::splitLine(line);
            for (Level* level : levels) {
                if (level->getFilename() == tokens.at(1)) currentLevel = level;
            }
        }
    }
}

bool DungeonCrawler::turn(){
    for (Character* character : currentLevel->getCharacters()) {
        if (AttackController* attack_controller = dynamic_cast<AttackController*>(character->getController())) {
            attack_controller->setTile(character->getTile());
        }
        Input input = character->getController()->move();
        if(input.getExit() == true) return false;
        character->setMoveDirection(input);
        Tile* currentTile = character->getTile();
        Tile* destTile = currentLevel->getTile(currentTile->getRow()+input.getDy(), currentTile->getColumn()+input.getDx());

        if (destTile->getTexture() == "E" && destTile != currentTile && character->isCharacterPlayer()) {
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

void DungeonCrawler::buildLevels(QDir dir){
    QDir levelsDir(dir);
    QStringList filters;
    filters << "*.csv";
    QFileInfoList files = levelsDir.entryInfoList(filters, QDir::Files, QDir::Name);
    for (const QFileInfo& fileInfo : files) {
        QString path = fileInfo.filePath();
        std::string stringPath = path.toStdString();
        Level* level = Level::CSVLoader(dynamic_cast<AbstractController*>(ui), stringPath);
        levels.push_back(level);
    }
    for (Level* level : levels) bindLevelchangers(level);
}

void DungeonCrawler::bindLevelchangers(Level* level) {
    std::ifstream in(level->getFilename());
    std::string line;
    while (std::getline(in, line)) {
        if (line == "#LEVELCHANGERS") {
            while (std::getline(in, line) && !line.empty()) {
                std::vector<std::string> tokens = Level::splitLine(line);
                int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
                int destLevelIndex = std::stoi(tokens.at(3)) - 1;
                int destRow = std::stoi(tokens.at(4)), destCol = std::stoi(tokens.at(5));
                auto iter = levels.begin();
                for (int i = 0; i < destLevelIndex; ++i) ++iter;
                Level* destLevel = *iter;
                dynamic_cast<Levelchanger*>(level->getTile(row, col))->setDestination(destLevel->getTile(destRow, destCol));
            }
        }
    }
}

void DungeonCrawler::saveGame() {
    std::ofstream state("../Save/State.csv");
    std::string levelFileName = "../Save/" + std::filesystem::path(currentLevel->getFilename()).filename().string();
    state << "#LOCATION\n" << "currentLevel," << levelFileName << "\n";
    for (Level* level : levels) {
        std::string baseFile = level->getFilename();
        std::string destFile = "../Save/" + std::filesystem::path(baseFile).filename().string();
        std::ifstream in(baseFile);
        std::ofstream out(destFile);
        std::string line;
        while (std::getline(in, line)) {
            out << line << "\n";
            if (line == "#DOORS") {
                while (std::getline(in, line) && !line.empty()) {
                    std::vector<std::string> tokens = Level::splitLine(line);
                    int row = std::stoi(tokens.at(0)), col = std::stoi(tokens.at(1));
                    Door* door = dynamic_cast<Door*>(level->getTile(row, col));
                    out << row << "," << col << "," << (door->isOpen() ? "open" : "closed") << "\n";
                }
                out << "\n";
            }
            else if (line == "#CHARACTERS") {
                for (Character* ch : level->getCharacters()) {
                    bool mc = ch->isCharacterPlayer();
                    if (mc && levels.front() != level) continue;
                    int row = ch->getTile()->getRow(), col = ch->getTile()->getColumn();
                    AbstractController* controller = ch->getController();
                    int currentHP = ch->getHitpoints();
                    std::string controllerType = "player";
                    if (dynamic_cast<StationaryController*>(controller)) controllerType = "stationary";
                    else if (dynamic_cast<AttackController*>(controller)) controllerType = "attack";
                    else if (dynamic_cast<GuardController*>(controller)) {
                        controllerType = "guard";
                        int movementIndex = dynamic_cast<GuardController*>(controller)->getIndex();
                        out << "npc" << "," << row << "," << col << "," << controllerType << "," << currentHP << "," << movementIndex << "\n";
                        continue;
                    }
                    out << (mc ? "main" : "npc") << "," << row << "," << col << "," << controllerType << "," << currentHP << "\n";
                }
                while (std::getline(in, line) && !line.empty()) {}
                out << "\n";
            }
        }
    }
}


