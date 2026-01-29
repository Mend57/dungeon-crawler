#ifndef DUNGEONCRAWLER_GUARDCONTROLLER_H
#define DUNGEONCRAWLER_GUARDCONTROLLER_H
#include "AbstractController.h"

class GuardController : public AbstractController {
  private:
    Input left = {-1,0};
    Input right = {1,0};
    int index = 0;
    std::vector<Input> inputs = {right,right,left,left,left,left,right,right};

  public:
    Input move() override {
      if (index >= inputs.size()) index = 0;
      return inputs.at(index++);
    }
    void decrementIndex() {index--;}
    void setIndex(int index) {this->index = index;}
    int getIndex() {return index;}
};

#endif