#include "GraphicalUI.h"

#include "GuardController.h"
#include "StationaryController.h"
#include "Tiles/Door.h"
#include "Tiles/Levelchanger.h"
#include "Tiles/Lootchest.h"
#include "Tiles/Pit.h"

std::map<std::string, QPixmap> GraphicalUI::floorTextures;
std::map<std::string, QPixmap> GraphicalUI::portalTextures;
std::map<std::string, QPixmap> GraphicalUI::stringToLabel;
std::map<std::string, QPixmap> GraphicalUI::characterTextures;
std::map<std::string, QPixmap> GraphicalUI::textures;

GraphicalUI::GraphicalUI() {
    QDir dirTextures("../textures");
    QDir dirChar("../textures/char");
    QDir dirFloor("../textures/floor");
    QDir dirPortal("../textures/portal");
    QStringList filters;
    filters << "*.png";

    dirTextures.setNameFilters(filters);
    dirChar.setNameFilters(filters);
    dirFloor.setNameFilters(filters);
    dirPortal.setNameFilters(filters);

    addFilesToMap(textures, dirTextures.entryInfoList());
    addFilesToMap(characterTextures, dirChar.entryInfoList());
    addFilesToMap(floorTextures, dirFloor.entryInfoList());
    addFilesToMap(portalTextures, dirPortal.entryInfoList());

    buildStringToLabelMap();

    std::vector<Level*> levels = buildLevels();

    startScreen = new StartScreen(this, levels);
    mainWindow = new MainWindow(this);

    startScreen->show();
}

void GraphicalUI::addFilesToMap(std::map<std::string, QPixmap>& map, const QFileInfoList& fileList) {
    for (const QFileInfo &fileInfo : fileList) {
        QString name = fileInfo.baseName();
        QPixmap pixmap(fileInfo.filePath());
        if (!pixmap.isNull()) {
            map[name.toStdString()] = pixmap;
        }
    }
}

void GraphicalUI::switchWindow() {
    startScreen->hide();
    mainWindow->show();
}

void GraphicalUI::buildStringToLabelMap() {
    stringToLabel["#"] = getTexture("wall1");
    stringToLabel["_"] = getTexture("pit");
    stringToLabel["<"] = getTexture("ramp");
    stringToLabel["X"] = getTexture("door_closed");
    stringToLabel["/"] = getTexture("door_opened");
    stringToLabel["?"] = getTexture("switch");
    stringToLabel["E"] = getTexture("levelchanger");
    stringToLabel["V"] = getTexture("chest");
}

void GraphicalUI::drawLevel(Level* level){
    std::vector<std::vector<Tile*>> tileMap = level->getTileMap();
    mainWindow->clearGridLayout();
    for (int row = 0; row < level->getHeight(); row++) {
        for (int col = 0; col < level->getWidth(); col++) {
            Tile* pos = tileMap[row][col];
            QLabel* label = pos->getLabel();
            label->setMinimumSize(30,30);
            label->setMaximumSize(300,300);
            label->setScaledContents(true);
            label->setAttribute(Qt::WA_TranslucentBackground);
            mainWindow->addToGridLayout(label, row, col);
        }
    }
}

void GraphicalUI::draw(Level* level) {
    std::vector<std::vector<Tile*>> tileMap = level->getTileMap();
    mainWindow->updateStatusBar();
    for (Character* character : level->getCharacters()) {
        QLabel* characterLabel = character->getLabel();
        characterLabel->setMinimumSize(30,30);
        characterLabel->setMaximumSize(300,300);
        characterLabel->setScaledContents(true);
        characterLabel->setAttribute(Qt::WA_TranslucentBackground);
        int row = character->getTile()->getRow();
        int col = character->getTile()->getColumn();
        Tile* pos = tileMap[row][col];
        if (dynamic_cast<Pit*>(pos)) characterLabel->lower();
        mainWindow->addToGridLayout(characterLabel, row, col);
        if (character->isCharacterPlayer() && dynamic_cast<Lootchest*>(pos)) mainWindow->endGame(true);
    }
}

std::vector<Level*> GraphicalUI::buildLevels(){
    Level* level1 = new Level(10, 10, this, {
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

    Level* level2 = new Level(10, 10, this, {
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
    for (int i = 0; i < level1->getHeight(); i++) {
        for (int j = 0; j < level1->getWidth(); j++) {
            Tile* tile1 = level1->getTile(i, j);
            Tile* tile2 = level2->getTile(i, j);
            if (tile1->getTexture() == "E") {
                Levelchanger* levelchanger1 = dynamic_cast<Levelchanger*>(tile1);
                if (levelchanger1) levelchanger1->setDestination(tile2);
            }

            if (tile2->getTexture() == "E") {
                Levelchanger* levelchanger2 = dynamic_cast<Levelchanger*>(tile2);
                if (levelchanger2) levelchanger2->setDestination(tile1);
            }
        }
    }
    Character* mainCharacter = new Character(level1->getTile(2,3), this, 10, 10);
    Character* stationary = new Character(level1->getTile(2,3), new StationaryController(), 10, 10);
    Character* guard1 = new Character(level1->getTile(2,3), new GuardController(), 5, 5);
    Character* guard2 = new Character(level1->getTile(2,3), new GuardController(), 5, 5);
    level1->setMainCharacter(mainCharacter);
    level1->placeCharacter(mainCharacter,2,3);
    level1->placeCharacter(stationary,3,1);
    level1->placeCharacter(guard1,5,5);
    level1->placeCharacter(guard2,7,5);
    level2->setMainCharacter(mainCharacter);

    std::vector<Level*> levels;
    levels.push_back(level1);
    levels.push_back(level2);
    return levels;
}

Input GraphicalUI::move() {return mainWindow->getInput();}
