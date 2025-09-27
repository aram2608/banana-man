#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <raylib.h>

class Platform {
  public:
    Platform();
    void draw();
    Rectangle get_rect();
    Vector2 pos;
    Vector2 size;

  private:
};

#endif