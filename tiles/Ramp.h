#ifndef DUNGEONCRAWLER_RAMP_H
#define DUNGEONCRAWLER_RAMP_H
#include "Floor.h"

class Ramp : public Floor {
    public:
      Ramp(const int row, const int column) : Tile(row, column, "<"), Floor(row, column){}
};

#endif