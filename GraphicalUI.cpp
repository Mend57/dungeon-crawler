#include "GraphicalUI.h"

#include "Tiles/Door.h"
#include "Tiles/Levelchanger.h"
#include "Tiles/Pit.h"

std::map<std::string, QPixmap> GraphicalUI::floorTextures;
std::map<std::string, QPixmap> GraphicalUI::portalTextures;
std::map<std::string, QPixmap> GraphicalUI::stringToLabel;
std::map<std::string, QPixmap> GraphicalUI::characterTextures;

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
}

void GraphicalUI::draw(Level* level) {
    std::vector<std::vector<Tile*>> tileMap = level->getTileMap();
    mainWindow->updateStatusBar();
    for (int row = 0; row < level->getHeight(); row++) {
        for (int col = 0; col < level->getWidth(); col++) {
            Tile* pos = tileMap[row][col];
            QLabel* label = pos->getLabel();
            label->setFixedSize(30,30);
            label->setScaledContents(true);
            label->setAttribute(Qt::WA_TranslucentBackground);
            label->raise();
            mainWindow->addToGridLayout(label, row, col);
            if (pos->hasCharacter()) {
                QLabel* characterLabel = pos->getCharacter()->getLabel();
                characterLabel->setFixedSize(30,30);
                characterLabel->setScaledContents(true);
                characterLabel->setAttribute(Qt::WA_TranslucentBackground);
                if (dynamic_cast<Pit*>(pos)) {
                    characterLabel->lower();
                }
                else {
                    characterLabel->raise();
                    characterLabel->raise();
                }
                mainWindow->addToGridLayout(characterLabel, row, col);
            }
        }
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
          "#...?....#"
          "##########"
      });
    for (int i = 0; i < level1->getHeight(); i++) {
        for (int j = 0; j < level1->getWidth(); j++) {
            Tile* t1 = level1->getTile(i, j);
            Tile* t2 = level2->getTile(i, j);
            if (t1->getTexture() == "E") {
                Levelchanger* lc1 = dynamic_cast<Levelchanger*>(t1);
                if (lc1) lc1->setDestination(t2);
            }

            if (t2->getTexture() == "E") {
                Levelchanger* lc2 = dynamic_cast<Levelchanger*>(t2);
                if (lc2) lc2->setDestination(t1);
            }
        }
    }
    Character* mainCharacter = new Character(level1->getTile(2,3), this, 10, 10);
    level1->setMainCharacter(mainCharacter);
    level1->placeCharacter(mainCharacter,2,3);
    level2->setMainCharacter(mainCharacter);

    std::vector<Level*> levels;
    levels.push_back(level1);
    levels.push_back(level2);
    return levels;
}

Input GraphicalUI::move() {return mainWindow->getInput();}
