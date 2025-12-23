#include <QApplication>

#include "DungeonCrawler.h"
#include "GraphicalUI.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    GraphicalUI gui;
    Level* level = new Level(10, 10, &gui);
    DungeonCrawler* dungeonCrawler = new DungeonCrawler(&gui, level);
    dungeonCrawler->turn();
    return app.exec();
}


