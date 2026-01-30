#ifndef DUNGEONCRAWLER_GRAPHICALUI_H
#define DUNGEONCRAWLER_GRAPHICALUI_H
#include <map>
#include <QDir>
#include <QString>
#include "UI/StartScreen.h"
#include "UI/MainWindow.h"
#include "AbstractView.h"
#include "controllers/AbstractController.h"
#include "DungeonCrawler.h"

class MainWindow;
class StartScreen;

class GraphicalUI : public AbstractView, public AbstractController{
    private:
        static std::map<std::string, QPixmap> floorTextures;
        static std::map<std::string, QPixmap> portalTextures;
        static std::map<std::string, QPixmap> stringToLabel;
        static std::map<std::string, QPixmap> characterTextures;
        static std::map<std::string, QPixmap> textures;
        StartScreen* startScreen;
        MainWindow* mainWindow;

        void buildStringToLabelMap();
        void addFilesToMap(std::map<std::string, QPixmap>& map, const QFileInfoList& fileList);

    public:
        GraphicalUI();
        static QPixmap getLabelFromString(const std::string& texture) {return stringToLabel[texture];}
        static QPixmap getFloorTexture(const std::string& texture) {return floorTextures[texture];}
        static QPixmap getPortalTexture(const std::string& texture) {return portalTextures[texture];}
        static std::map<std::string, QPixmap> getPortalTextures() {return portalTextures;}
        void draw(Level* level) override;
        void drawLevel(Level* level) override;
        Input move() override;
        static QPixmap getTexture(const std::string& texture) {return textures[texture];}
        static QPixmap getCharacterTexture(const std::string& texture) {return characterTextures[texture];}
        StartScreen* getStartScreen() const {return startScreen;}
        MainWindow* getMainWindow() const {return mainWindow;}
        void switchWindow() const;
};

#endif