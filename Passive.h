#ifndef DUNGEONCRAWLER_PASSIVE_H
#define DUNGEONCRAWLER_PASSIVE_H

class Passive {
  public:
    virtual ~Passive() = default;
    virtual void notify() = 0;
};

#endif