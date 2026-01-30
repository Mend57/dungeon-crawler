#ifndef DUNGEONCRAWLER_ACTIVE_H
#define DUNGEONCRAWLER_ACTIVE_H
#include <vector>
#include "Passive.h"

class Active {
  private:
    std::vector<Passive*> passiveObjects;

  public:
    std::vector<Passive*> getPassiveObject(){return passiveObjects;}
    void activate(){for (Passive* passiveObject : passiveObjects) passiveObject->notify();}
    void detach(Passive* passiveObject){std::erase(passiveObjects, passiveObject);}
    void attach(Passive* passiveObject) {
      for (const Passive* passiveObj : passiveObjects) if (passiveObj == passiveObject) return;
      passiveObjects.push_back(passiveObject);
    }
};

#endif
