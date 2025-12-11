#ifndef DUNGEONCRAWLER_GRAPHICALUI_H
#define DUNGEONCRAWLER_GRAPHICALUI_H
#include "AbstractView.h"
#include <map>
#include <QPixmap>
#include <QDir>
#include <QString>
#include <QLabel>
#include "StartScreen.h"
#include "MainWindow.h"
#include "AbstractController.h"

class Level;
class MainWindow;
class StartScreen;

class GraphicalUI : public AbstractView, public AbstractController{
    private:
        std::map<std::string, QPixmap> characterTextures;
        static std::map<std::string, QPixmap> floorTextures;
        static std::map<std::string, QPixmap> portalTextures;
        std::map<std::string, QPixmap> textures;
        static std::map<std::string, QPixmap> stringToLabel;
        StartScreen* startScreen;
        MainWindow* mainWindow;

        void buildStringToLabelMap();
        void addFilesToMap(std::map<std::string, QPixmap>& map, const QFileInfoList& fileList);

    public:
        GraphicalUI();
        void draw(Level* level) override;
        Input move() override;
        QPixmap getTexture(const std::string& texture) {return textures[texture];}
        static QPixmap getLabelFromString(const std::string texture) {return stringToLabel[texture];}
        static QPixmap getFloorTexture(const std::string& texture) {return floorTextures[texture];}
        static QPixmap getPortalTexture(const std::string& texture) {return portalTextures[texture];}
        static std::map<std::string, QPixmap> getPortalTextures() {return portalTextures;}
        QPixmap getCharacterTexture(const std::string& texture) {return characterTextures[texture];}
        void switchWindow();
};


#endif