#include "GraphicalUI.h"

#include "Tiles/Door.h"
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

    startScreen = new StartScreen(this);
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
}

void GraphicalUI::draw(Level* level) {
    std::vector<std::vector<Tile*>> tileMap = level->getTileMap();
    for (int row = 0; row < level->getHeight(); row++) {
        for (int col = 0; col < level->getWidth(); col++) {
            Tile* pos = tileMap[row][col];
            QLabel* label = pos->getLabel();
            label->setFixedSize(30,30);
            label->setScaledContents(true);
            label->setAttribute(Qt::WA_TranslucentBackground);
            mainWindow->addToGridLayout(label, row, col);
            if (pos->hasCharacter()) {
                QLabel* characterLabel = pos->getCharacter()->getLabel();
                characterLabel->setFixedSize(30,30);
                characterLabel->setScaledContents(true);
                characterLabel->setAttribute(Qt::WA_TranslucentBackground);
                if (dynamic_cast<Pit*>(pos)) characterLabel->lower();
                else characterLabel->raise();
                mainWindow->addToGridLayout(characterLabel, row, col);
            }
        }
    }
}

Input GraphicalUI::move() {return mainWindow->getInput();}
