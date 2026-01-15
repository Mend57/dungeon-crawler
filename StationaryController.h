#ifndef DUNGEONCRAWLER_STATIONARYCONTROLLER_H
#define DUNGEONCRAWLER_STATIONARYCONTROLLER_H
#include "AbstractController.h"

class StationaryController : public AbstractController {
    Input move() override{return {0, 0};}
};


#endif