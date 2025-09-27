#ifndef BMAN_HPP
#define BMAN_HPP

#include <raylib.h>

class BananaMan {
  public:
    BananaMan();
    void draw();
    void update();
    void keyboard();
    Rectangle get_rect();
    bool grounded;
    bool dj;
    Vector2 pos;
    Vector2 size;
    Vector2 velocity;
    float gravity;
    float speed;

  private:
    void double_jump();
};

#endif