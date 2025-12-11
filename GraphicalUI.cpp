#include "GraphicalUI.h"


std::map<std::string, QPixmap> GraphicalUI::floorTextures;
std::map<std::string, QPixmap> GraphicalUI::portalTextures;
std::map<std::string, QPixmap> GraphicalUI::stringToLabel;

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

void GraphicalUI::switchWindow()
{
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

void GraphicalUI::draw(Level *level){};
Input GraphicalUI::move(){};
