#ifndef RECT
#define RECT
#include "pod.hpp"
#include "shape.hpp"
#include <iostream>
namespace malashenko {
  struct Rectangle : Shape {
    Rectangle(double width, double height, point_t pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    double width_, height_;
    point_t pos_;
  };
}
#endif
