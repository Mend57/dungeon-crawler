#ifndef TERMINALUI_H
#define TERMINALUI_H
#include "AbstractController.h"
#include "AbstractView.h"
#include <iostream>
#include <set>

class TerminalUI: public AbstractView, public AbstractController {
  public:
    void draw(Level* level) override;
    Input move() override;
};

#endif
