#ifndef DUNGEONCRAWLER_ABSTRACTCONTROLLER_H
#define DUNGEONCRAWLER_ABSTRACTCONTROLLER_H
#include "Input.h"

class AbstractController {
    public:
      virtual ~AbstractController() = default;
      virtual Input move() = 0;
};

#endif