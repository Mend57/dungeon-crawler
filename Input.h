#ifndef INPUT_H
#define INPUT_H

class Input{
  private:
    int dx;
    int dy;
    int exit;

  public:
    Input(const int dx, const int dy) : dx(dx), dy(dy), exit(false){};
    Input(const int exit) : dx(0), dy(0), exit(exit){};

    int getExit() const{return exit;}
    int getDx() const{return dx;}
    int getDy() const{return dy;}
};

#endif
