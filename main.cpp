#include <QApplication>

#include "DungeonCrawler.h"
#include "GraphicalUI.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    GraphicalUI gui;
    return app.exec();
}


